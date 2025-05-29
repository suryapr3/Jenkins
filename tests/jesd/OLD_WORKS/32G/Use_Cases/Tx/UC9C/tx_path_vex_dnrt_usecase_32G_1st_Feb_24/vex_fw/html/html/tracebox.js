function turn_highlight(e, on_or_off)
{
  parent.document.getElementById(e.currentTarget.id).setAttribute("state", on_or_off);
  e.currentTarget.setAttribute("state", on_or_off);
}

function turn_on_highlight(e)
{
  var e = window.event || e;
  turn_highlight(e, "selected");
}

function turn_off_highlight(e)
{
  var e = window.event || e;
  turn_highlight(e, "normal");
}


function install_hooks()
{
  divs=document.getElementsByTagName("CODE")
  for (var i = 0; i < divs.length; i++) {
    if (divs[i].getAttribute("class")!="ref_op") continue;
    divs[i].onmouseover=turn_on_highlight
    divs[i].onmouseout=turn_off_highlight
  }
}
