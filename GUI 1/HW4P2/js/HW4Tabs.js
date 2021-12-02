/*
File: js/HW4Tabs.js
GUI Assignment 4: Using the jQuery Plugin/UI with Your Dynamic Table
Part 2: jQuery UI Slider and Tab Widgets

This webpage creates a dynamic multiplication table based on user input using HTML, CSS, and JavaScript. 
The user input is now validated with jQeury.
The user can now adjust form values with jQuery sliders, and save tables with jQuery tabs.

Peyton Somerville
11/6/2021
*/

// keep track of how many tabs there are
var tabCount = 0;

document.querySelector("#saveBtn").onclick = function() {
    // only generate tab if form is valid
    var valid = $("#inputForm").validate().checkForm();
    if (!valid) {
        return false;
    }

    // since form is valid increase tab count
    tabCount++;

    // initialize jQuery tabs
    $("#savedTables").tabs();

    // get values for tab headers
    var minColVal = Number(document.getElementById("minColVal").value);
    var maxColVal = Number(document.getElementById("maxColVal").value);
    var minRowVal = Number(document.getElementById("minRowVal").value);
    var maxRowVal = Number(document.getElementById("maxRowVal").value);

    // build HTML for tab headers
    var tabList = "<li class='tab'>";
    tabList += "<a href='#" + tabCount + "'>(" + minColVal + " to " + maxColVal + ") x (" + minRowVal + " to " + maxRowVal + ")</a>"
    tabList += "<span class='ui-icon ui-icon-close' role='presentation'></span></li>";
    document.querySelector("#savedTablesList").insertAdjacentHTML("beforeend", tabList);

    // build HTML for tab content
    var table = document.querySelector("#multTable").innerHTML;
    var tabContent = "<div id='" + tabCount + "'>";
    tabContent += table;
    tabContent += "</div>";
    document.querySelector("#savedTables").insertAdjacentHTML("beforeend", tabContent);

    // update tabs
    $("#savedTables").tabs("refresh");
    $("#savedTables").tabs("option", "active", -1);

    // handles deleting tabs
    $("#savedTables").delegate( "span.ui-icon-close", "click", function() {
        var tabNum = $(this).closest("li").remove().attr("aria-controls");
        $("#" + tabNum).remove();

        try {
            $("#savedTables").tabs("refresh");
        }
        catch (e) {
            // console.log(e);
        }

        if($("li.tab").length == 0) {
            try {
                $("#savedTables").tabs("destroy");
            }
            catch (e) {
                // console.log(e);
            }

            return false;
        }
    });

    return false;
}
