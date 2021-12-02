/*
File: js/HW4P2JavaScript.js
GUI Assignment 4: Using the jQuery Plugin/UI with Your Dynamic Table
Part 2: jQuery UI Slider and Tab Widgets

This webpage creates a dynamic multiplication table based on user input using HTML, CSS, and JavaScript. 
The user input is now validated with jQeury.
The user can now adjust form values with jQuery sliders, and save tables with jQuery tabs.

Peyton Somerville
11/6/2021
*/

// called when document is ready to initialize sliders
$(function() {
    // slider rules
    $("#minColSlider").slider({
        min: -15,
        max: 15,
        value: 1,
        slide: function(event, ui) {
            $("#minColVal").val(ui.value);

            // generate table with every update to the slider
            genTable();
        }
    });

    // two-way binding
    $("#minColVal").val($("#minColSlider").slider("value"));
    $("#minColVal").change(function() {

        var oldVal = $("#minColSlider").slider("value");
        var newVal = $(this).val();

        if (isNaN(newVal)) {
            $("#minColSlider").slider("value", oldVal); 
        }
        else {
            $("#minColSlider").slider("value", newVal);
        }

        // generate table with every update to the input box
        genTable();
    });

    // same thing for rest of the sliders
    $("#maxColSlider").slider({
        min: -15,
        max: 15,
        value: 10,
        slide: function(event, ui) {
            $("#maxColVal").val(ui.value);
            genTable();
        }
    });

    $("#maxColVal").val($("#maxColSlider").slider("value"));
    $("#maxColVal").change(function() {
        var oldVal = $("#maxColSlider").slider("value");
        var newVal = $(this).val();

        if (isNaN(newVal)) {
            $("#maxColSlider").slider("value", oldVal); 
        }
        else {
            $("#maxColSlider").slider("value", newVal);
        }

        genTable();
    });


    $("#minRowSlider").slider({
        min: -15,
        max: 15,
        value: 1,
        slide: function(event, ui) {
            $("#minRowVal").val(ui.value);
            genTable();
        }
    });

    $("#minRowVal").val($("#minRowSlider").slider("value"));
    $("#minRowVal").change(function() {
        var oldVal = $("#minRowSlider").slider("value");
        var newVal = $(this).val();

        if (isNaN(newVal)) {
            $("#minRowSlider").slider("value", oldVal); 
        }
        else {
            $("#minRowSlider").slider("value", newVal);
        }

        genTable();
    });


    $("#maxRowSlider").slider({
        min: -15,
        max: 15,
        value: 10,
        slide: function(event, ui) {
            $("#maxRowVal").val(ui.value);
            genTable();
        }
    });

    $("#maxRowVal").val($("#maxRowSlider").slider("value"));
    $("#maxRowVal").change(function() {
        var oldVal = $("#maxRowSlider").slider("value");
        var newVal = $(this).val();

        if (isNaN(newVal)) {
            $("#maxRowSlider").slider("value", oldVal); 
        }
        else {
            $("#maxRowSlider").slider("value", newVal);
        }

        genTable();
    });

    // generates default table on page initialization
    genTable();
});

function genTable() {

    // only generate table if form is valid
    if ($("#inputForm").valid() != true) {
        // clear any mult table that might already be there
        $("#multTable").empty();

        return false;
    }

    // get values from form
    var minColVal = Number(document.getElementById("minColVal").value);
    var maxColVal = Number(document.getElementById("maxColVal").value);
    var minRowVal = Number(document.getElementById("minRowVal").value);
    var maxRowVal = Number(document.getElementById("maxRowVal").value);
    // console.log(minColVal, maxColVal, minRowVal, maxRowVal);

    // check if min > max (lessThan and greaterThan with jQuery is buggy)
    if (minColVal > maxColVal) {
        var tempCol = minColVal;
        minColVal = maxColVal;
        maxColVal = tempCol;
    }
    if (minRowVal > maxRowVal) {
        var tempRow = minRowVal;
        minRowVal = maxRowVal;
        maxRowVal = tempRow;
    }

    // initialize matrix
    var colSize = maxColVal - minColVal + 1
    var rowSize = maxRowVal - minRowVal + 1
    var arr = new Array(rowSize);
    for (var i = 0; i < rowSize; i++) {
        arr[i] = new Array(colSize);
    }

    // fill matrix
    var x = minColVal;
    var y = minRowVal;
    var product;
    var prodCommas;
    for (var i = 0; i < rowSize; i++) {
        for (var j = 0; j < colSize; j++) {
            product = x * y;
            if (product >= 1000 || product <= -1000) {	// insert commas
                prodCommas = product.toString().replace(/\B(?=(\d{3})+(?!\d))/g, ",");
                arr[i][j] = prodCommas;
            }
            else {
                arr[i][j] = product;
            }
            x++;
        }
        x = minColVal;
        y++;
    }


    // building the html for the table
    var table = "<table>";
    table += "<tr>";
    table += "<th>*</th>";
    for (var i = minColVal; i <= maxColVal; i++) {
        table += "<th>" + i + "</th>";
    }
    table += "</tr>";
  
    var rowNum = minRowVal;
    for (var i = 0; i < rowSize; i++) {
        table += "<tr>";
        table += "<td>" + rowNum++ + "</td>";
        for (var j = 0; j < colSize; j++) {
            table += "<td>" + arr[i][j] + "</td>";
        }
        table += "</tr>";
    }

    table += "</table>";
    document.getElementById("multTable").innerHTML = table;

    return false;
}