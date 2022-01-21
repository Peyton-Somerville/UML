/*
File: js/HW4P1JavaScript.js
GUI Assignment 4: Using the jQuery Plugin/UI with Your Dynamic Table 
Part 1: Validation Plugin 

This webpage creates a dynamic multiplication table based on user input using HTML, CSS, and JavaScript.
The user input is now validated with jQeury.

Peyton Somerville
11/6/2021
*/

document.querySelector("#submitBtn").onclick = function() {

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

    // check if min > max (lessThan and greaterThan with jQuery is buggy)
    if (minColVal > maxColVal) {
        var tempCol = minColVal;
        minColVal = maxColVal;
        maxColVal = tempCol;
        document.getElementById("minColVal").value = minColVal;
        document.getElementById("maxColVal").value = maxColVal;
    }
    if (minRowVal > maxRowVal) {
        var tempRow = minRowVal;
        minRowVal = maxRowVal;
        maxRowVal = tempRow;
        document.getElementById("minRowVal").value = minRowVal;
        document.getElementById("maxRowVal").value = maxRowVal;
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