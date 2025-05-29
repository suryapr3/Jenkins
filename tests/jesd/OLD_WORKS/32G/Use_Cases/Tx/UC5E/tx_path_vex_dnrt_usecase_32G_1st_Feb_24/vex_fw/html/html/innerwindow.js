/*

    InWin: Simple Inner Window Management
    
*/
InWin = {
    _navbar: null,
    _move: null,
    _down: null,
    _focus: null,
    _offset: null,
    _target: null,

    initializeAllWindows: function (){
        var wins = getElementsByTagAndClassName('DIV', 'window');
        InWin._navbar = getFirstElementByTagAndClassName ('DIV', 'navigator_bar');
        InWin.detachWindows (wins);
        forEach(wins,
                function(elem) {
                    InWin.makeWindowControl (elem);
                    InWin.initWindow (elem);
                });
    },
    detachWindows: function (wins) {
        var poss = map (function (w) { return getElementPosition (w); }, wins);
        map (function (w,p) {
                updateNodeAttributes (w, {'style' : { 'position': 'absolute' }});
                if(p) setElementPosition (w, p);
            },
            wins, poss);
    },
    makeWindowControl: function (win) {
        if (!InWin._navbar) return;
        winctrl = DIV ({'class': 'window_control'}, getNodeAttribute (win, 'id'));
        if (hasElementClass (win, 'window_minimized')) {
            toggleElementClass ('window_control_minimized', winctrl);
        }
        appendChildNodes (InWin._navbar, winctrl);
        winctrl.toggleMinimize = function (e) {
            toggleElementClass ('window_control_minimized', this);
        };
        connect (win, "toggle_minimize", winctrl, 'toggleMinimize');
        connect(winctrl, 'onclick',
                function (e) {
                    e.stop;
                    InWin.toggleMinimizeWindow (win);
                } );
    },
    initWindow: function (win) {
        nd_title   = getFirstElementByTagAndClassName('DIV', 'window_title',win);
        nd_content = getFirstElementByTagAndClassName(null, 'window_content',win);
        appendChildNodes (nd_title,
                          DIV ({'class':'minimizer'},null));
        updateNodeAttributes (nd_content, { 'style': { 'max-width': window.innerWidth+'px' } });
        cnt = TABLE ({'class': 'window'},
                     TBODY (null,
                            [ TR (null, [ TD ({'id':'window_top_left'},null),
                                          TD ({'id':'window_top_middle', 'class': 'dragger' }, nd_title),
                                          TD ({'id':'window_top_right'}, null)]),

                              TR (null, [ TD ({'id':'window_center_left'},null),
                                          TD ({'id':'window_center_middle'},nd_content),
                                          TD ({'id':'window_center_right'},null)]),

                              TR (null, [ TD ({'id':'window_bottom_left'},null),
                                          TD ({'id':'window_bottom_middle'},null),
                                          TD ({'id':'window_bottom_right', 'class': 'resizer' },null)])
                              ])
                     );
        replaceChildNodes (win, cnt);
        connect(win, 'onclick', InWin.focusWindow);
        forEach(getElementsByTagAndClassName(null, 'minimizer', win),
                function(elem) {
                    connect(elem, 'onclick',
                            function (e) {
                                var win = getFirstParentByTagAndClassName (e.target(), 'DIV', 'window');
                                InWin.toggleMinimizeWindow (win);
                            });
                });
        forEach(getElementsByTagAndClassName('TD', 'dragger', win),
                function(elem) {
                    connect(elem, 'onmousedown', InWin.moveWindow);
                });
        forEach(getElementsByTagAndClassName('TD', 'resizer', win),
                function(elem) {
                    connect(elem, 'onmousedown', InWin.resizeWindow);
                });
    },
    focusWindow: function(e) {
        var _target = getFirstParentByTagAndClassName (e.target(), 'DIV', 'window');
        InWin._focus (_target);
    },
    openWindow: function (win) {
        if (hasElementClass (win, 'window_minimized')) {
            toggleMinimizeWindow (win);
        }
    },
    toggleMinimizeWindow: function (win) {
        signal (win, "toggle_minimize");
        toggleElementClass ('window_minimized', win);
        if (!hasElementClass (win, 'window_minimized')) {
            into = getFirstElementByTagAndClassName(null, 'window_content',win);
            if (Inject) Inject.injectInElement (into);
            InWin._focus (win);
        }
    },
    moveWindow: function(e) {
        e.stop();
        InWin._target = getFirstParentByTagAndClassName (e.target(), 'DIV', 'window');
        InWin._focus (InWin._target);
        pos = new MochiKit.Style.Coordinates (parseFloat (getStyle (InWin._target, 'left')),
                                              parseFloat (getStyle (InWin._target, 'top')));
        /*
            There's no cross-browser way to get offsetX and offsetY, so we
            have to do it ourselves. For performance, we do this once and
            cache it.
        */
        InWin._offset = InWin._diff(e.mouse().page, pos);
        InWin._move = connect(document, 'onmousemove', InWin._moveDrag);
        InWin._down = connect(document, 'onmouseup', InWin._stop);
    },
    resizeWindow: function(e) {
        e.stop();

        win = getFirstParentByTagAndClassName (e.target(), 'DIV', 'window');
        InWin._target = getFirstElementByTagAndClassName(null, 'window_content', win);
        InWin._offset = InWin._sub (getElementDimensions (InWin._target), e.mouse().page);
        InWin._move = connect(document, 'onmousemove', InWin._resizeDrag);
        InWin._down = connect(document, 'onmouseup', InWin._stop);
    },

    _diff: function(lhs, rhs) {
        return new MochiKit.Style.Coordinates(lhs.x - rhs.x, lhs.y - rhs.y);
    },
    _add: function(dim, ofs) {
        return new MochiKit.Style.Dimensions(dim.w + ofs.x, dim.h + ofs.y);
    },
    _sub: function(dim, ofs) {
        return new MochiKit.Style.Dimensions(dim.w - ofs.x, dim.h - ofs.y);
    },
    _focus: function (win) {
        if(InWin._focussed_window) {
            updateNodeAttributes (InWin._focussed_window, { 'style' : { 'z-index': '0'} });
        }
        InWin._focussed_window = win;
        updateNodeAttributes (InWin._focussed_window, { 'style' : { 'z-index': '1' } });
    },
    _moveDrag: function(e) {
        e.stop();
        dif = InWin._diff(e.mouse().page, InWin._offset);
        setElementPosition(
            InWin._target,
            dif);
    },
    _resizeDrag: function(e) {
        e.stop();
        dim = InWin._add(InWin._offset, e.mouse().page);
        setElementDimensions(
            InWin._target,
            dim);
    },
    
    _stop: function(e) {
        disconnect(InWin._move);
        disconnect(InWin._down);
    }
};

connect(window, 'onload', InWin.initializeAllWindows);
