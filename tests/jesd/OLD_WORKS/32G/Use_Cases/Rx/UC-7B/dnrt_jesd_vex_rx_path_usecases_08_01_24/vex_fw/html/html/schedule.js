function select_operation(target, state)
{
  target.setAttribute("state", state);
  loc=target.getAttribute("hive:location");
  lines=document.getElementsByName(loc);
  for (var i = 0; i < lines.length; i++) {
    lines[i].setAttribute("state", state);
  }
}

function focus_operation(target)
{
  loc=target.getAttribute("hive:location");
  location.href=location.href.replace (/#.*$/,'') + "#" + loc;
}

function show_tracebox(e)
{
  var e = window.event || e;
}

function turn_on_source_highlight(e)
{
  var e = window.event || e;
  select_operation(e.currentTarget, "selected");
  add_reguses (e.currentTarget, "on");
  add_regdefs (e.currentTarget, "on");
}

function turn_off_source_highlight(e)
{
  var e = window.event || e;
  select_operation(e.currentTarget, "");
  add_reguses (e.currentTarget, "");
  add_regdefs (e.currentTarget, "");
}

var old_tracebox
var tracebox_div

function show_tracebox(e)
{
  var e=window.event || e
  var mybox=document.getElementById('tracebox');
  var myframe=document.getElementById('traceframe');
  var myheader=document.getElementById('traceboxheader');
  mybox.onmousedown=tracebox_startmove
  var node=e.target.getAttribute('ID') + ".html"
  mybox.style.left       = 30 + e.clientX
  mybox.style.top        = 30 + e.clientY
  mybox.style.visibility = 'visible'
  myframe.setAttribute('src', node);

  myheader.innerHTML=e.target.innerHTML;

  e.currentTarget.setAttribute("tracing", "yes");
  if (old_tracebox) old_tracebox.setAttribute("tracing", "");
  old_tracebox = e.currentTarget;
}

var current_deps = []
var show_dep_levels = 0

function get_operation(label)
{
  operations=document.getElementsByName(label);
  if (operations && operations.length>0) {
    return operations[0];
  }
  return null
}

function set_operation_dep(operation, value)
{
  operation.setAttribute("dep", value);
  if (value != "") current_deps[show_dep_levels].push(operation);

  loc=operation.getAttribute("hive:location");
  lines=document.getElementsByName(loc);
  for (var i = 0; i < lines.length; i++) {
    lines[i].setAttribute("dep", value);
  }
}

function get_operation_dep(operation)
{
  var state = operation.getAttribute("dep");
  if (!state || state=="") return null;
  return state;
}

function clear_deps()
{
  var tds=document.getElementsByTagName("TD")
  for (var i = 0; i < tds.length; i++) {
    if (tds[i].getAttribute("class")!="operation") continue;
    tds[i].setAttribute("dep", "");
    tds[i].setAttribute("succ", "");
    tds[i].setAttribute("live", "");
  }

  for (var i = 0; i < tds.length; i++) {
    if (tds[i].getAttribute("class")!="pressure") continue;
    tds[i].setAttribute("used", "");
    tds[i].setAttribute("deffed", "");
  }

  var pres=document.getElementsByTagName("PRE")
  for (var i = 0; i < pres.length; i++) {
    if (pres[i].getAttribute("class")!="sourceline") continue;
    pres[i].setAttribute("dep", "");
    pres[i].setAttribute("succ", "");
  }
}

function add_successors(operation)
{
  var succs=eval(operation.id + "_succs")
  for (var i=0; i<succs.length; i++) {
    var operation = get_operation(succs[i])
    if (!operation) continue;
    operation.setAttribute("succ", "on");
  }
}

function add_reguses(operation,mode)
{
  var reguses=eval(operation.id + "_reguses")
  for (var i=0; i<reguses.length; i++) {
    var operation = get_operation(reguses[i])
    if (!operation) {
        continue;
    }
    operation.setAttribute("used", mode);
  }
}

function add_regdefs(operation,mode)
{
  var regdefs=eval(operation.id + "_regdefs")
  for (var i=0; i<regdefs.length; i++) {
    var operation = get_operation(regdefs[i])
    if (!operation) {
        continue;
    }
    if (mode=="on") {
      if (operation.getAttribute("used")=="on") {
          operation.setAttribute("used", "");
          operation.setAttribute("both", "on");
      } else {
          operation.setAttribute("deffed", mode);
      }
    } else {
      operation.setAttribute("deffed", mode);
      operation.setAttribute("both", mode);
    }
  }
}

function add_dependencies()
{
  last_deps=current_deps[show_dep_levels];
  show_dep_levels++;
  current_deps[show_dep_levels]=[]
  for (var i=0; i<last_deps.length; i++) {
    var last_dep=last_deps[i];
    var newdeps=eval(last_dep.id + "_deps")
    for (var j=0; j<newdeps.length; j++) {
      var operation = get_operation(newdeps[j]);
      if (!operation) continue;
      if (get_operation_dep(operation)) continue;
      set_operation_dep(operation, "level" + (show_dep_levels>4?4:show_dep_levels))
    }
  }
}

function show_deps(e)
{
  var e=window.event || e
  var label=e.target.getAttribute('ID')
  var operation=get_operation(label)
  
  if (get_operation_dep(operation) != "source") {
    clear_deps();
    show_dep_levels = 0;
    current_deps[0]=[];
    set_operation_dep(operation, "source");
    add_successors (operation);
    add_reguses (operation,"on");
    add_regdefs (operation,"on");
    focus_operation (operation);
  }
  add_dependencies()
}

function set_live_reg(operation,mode)
{
  var live=eval(operation.getAttribute('NAME') + "_live")
  
  for (var i=0; i<live.length; i++) {
    var operation = get_operation(live[i])
    if (!operation) {
        continue;
    }
    operation.setAttribute("live", mode);
  }
}

function turn_on_live_highlight(e)
{
  var e=window.event || e
  var label=e.target.getAttribute('NAME')
  var rfc=get_operation(label)

  e.currentTarget.setAttribute("state","selected")
  set_live_reg (rfc,"on");
}

function turn_off_live_highlight(e)
{
  var e=window.event || e
  var label=e.target.getAttribute('NAME')
  var rfc=get_operation(label)

  e.currentTarget.setAttribute("state","")
  set_live_reg (rfc,"");
}

var initmousex
var initmousey
var initx
var inity
var width
var target

function tracebox_startmove(e)
{
  var e = window.event || e;

  // remember client mouse position
  initmousex=e.clientX
  initmousey=e.clientY

  // remember box position
  initx=parseInt(this.offsetLeft)
  inity=parseInt(this.offsetTop)

  // hide contents
  var myframediv=document.getElementById('traceboxframediv');
  myframediv.style.visibility="hidden";

  // install hooks
  target=this
  document.onmousemove=move_tracebox
  document.onmouseup=stop_move_tracebox
}

function move_tracebox(e)
{
  var e=window.event || e
  // calcaulate the distance mouse travelled
  distancex=e.clientX-initmousex
  distancey=e.clientY-initmousey
  // adjust new position using the old (mousedown) position
  target.style.left=distancex+initx+"px"
  target.style.top=distancey+inity+"px"
}

function stop_move_tracebox()
{
  document.onmousemove=null
  document.onmouseup=null
  target=null

  // and show contents
  var myframediv=document.getElementById('traceboxframediv');
  myframediv.style.visibility="visible";
}

var tracebox_enabled = 0

function install_hooks() 
{
  current_deps[0]=[]
  tds=document.getElementsByTagName("TD")
  for (var i = 0; i < tds.length; i++) {
    if (tds[i].getAttribute("class")=="operation") {
      tds[i].onmouseover=turn_on_source_highlight;
      tds[i].onmouseout=turn_off_source_highlight;
      if (tracebox_enabled) tds[i].onclick=show_tracebox;
      else tds[i].onclick=show_deps;
    } else if (tds[i].getAttribute("class")=="pressure") {
      tds[i].onmouseover=turn_on_live_highlight;
      tds[i].onmouseout=turn_off_live_highlight;
    }
  }
}

function install_tracebox_hooks()
{
  tracebox_enabled = 1
  document.write('<div class="tracebox" id="tracebox"><div id="traceboxheader" class="traceboxheader"></div><div class="traceboxframediv" id="traceboxframediv"><iframe class="traceboxframe" id="traceframe" src=""></iframe></div></div>');
}

