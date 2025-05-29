/*
 * Usage:
 *  <a class="inject:html" href="schedule.html">loading...</a>
 *  <a class="inject:text" href="layer3.c">loading...</a>
 */
Inject = {
    _addLine: function (target,path,text,lineno,end)
    {
        appendChildNodes (target,
                          LI ({ 'class' : 'sourceline' },
                              PRE ({ 'class' : 'sourceline',
                                     'name' : path+':'+lineno},
                                  [A ({'name' : path+':'+lineno},null),
                                   text[lineno-1]
                                   ])));
        if (lineno<end) {
            callLater (0,Inject._addLine,target,path,text,lineno+1,end);
        }
    },
    injectInElement: function (into)
    {
        var text = getFirstElementByTagAndClassName('A', 'inject:text', into);
        var html = getFirstElementByTagAndClassName('A', 'inject:html', into);
        if (text) Inject._injectText (text.href, into, getNodeAttribute (text, 'href'));
        if (html) Inject._injectHTML (html.href, into, getNodeAttribute (html, 'href'));
    },
    _injectText: function (url, target, path)
    {
        var d = doXHR(url, { 'mimeType': 'text/plain',
                             'headers': [['Accept', 'application/text']]});
        d.addCallback (function (req) {
                var text = req.responseText.split(/\n/);
                var list = OL (null,null);
                replaceChildNodes(target, list);
                Inject._addLine (list,path,text,1,text.length);
            });
        d.addErrback (function (err) {
                alert ('could not load ' + url + ":" + err);
            });
    },
    _injectHTML: function (url, target, path)
    {
        var d = doXHR(url, { 'mimeType': 'text/html',
                             'headers': [['Accept', 'application/text']]});
        d.addCallback (function (req) {
                target.innerHTML = req.responseText;
                scripts = getElementsByTagAndClassName('SCRIPT', null, target);
                forEach (scripts,
                         function (s) {
                             if (getNodeAttribute (s, 'type')=="text/javascript") {
                                 eval (s.innerHTML);
                             }
                         });
            });
        d.addErrback (function (err) {
                alert ('could not load ' + url + ":" + err);
            });
    },
    injectInTable: function (table, anchor) {
        var url = getNodeAttribute (anchor, 'href');
        var d = doXHR(url, { 'mimeType': 'text/xml',
                             'headers': [['Accept', 'application/text']]});
        d.addCallback (function (req) {
                _injectInTable (table, req.responseXML);
            });
        d.addErrback (function (err) {
                alert ('could not load ' + url + ":" + err);
            });
    },
    _injectInTable: function (table, xml) {
        header  = xml.getElementsByTagName ('header')[0];
        columns = header.getElementsByTagName ('cell');
        forEach (getElementsByTagAndClassName ('TR', null, table),
                 function (row) {
                rowid = getNodeAttribute (row, 'id');
                entry = xml.getElementById (rowid);
                if (entry) {
                    cols = map (function (cell) { TD (null, scrapeText (cell)); },
                                entry.getElementsByTagName ('cell'));
                } else {
                    cols = [];
                }
                for(i=cols.size;i<columns.size;i++) {
                    cols.append (TD (null, null));
                }
                appendChildNodes (row, cols);
            });
    }
};
