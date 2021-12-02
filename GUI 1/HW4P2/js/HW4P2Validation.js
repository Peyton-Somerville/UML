/*
File: js/HW4P2Validation.js
GUI Assignment 4: Using the jQuery Plugin/UI with Your Dynamic Table
Part 2: jQuery UI Slider and Tab Widgets

This webpage creates a dynamic multiplication table based on user input using HTML, CSS, and JavaScript. 
The user input is now validated with jQeury.
The user can now adjust form values with jQuery sliders, and save tables with jQuery tabs.

Peyton Somerville
11/6/2021
*/

// called when document is ready to initialize validation
$(function() {

    $("#inputForm").validate({
        // custom rules for acceptable input
        rules: {
            minColVal: {
                required: true,
                number: true,
                integer: true,     
                min: -15,
                max: 15
            },
            maxColVal: {
                required: true,
                number: true,
                integer: true,      
                min: -15,
                max: 15
            },
            minRowVal: {
                required: true,
                number: true,
                integer: true,      
                min: -15,
                max: 15
            },
            maxRowVal: {
                required: true,
                number: true,
                integer: true,      
                min: -15,
                max: 15
            }
        },

        // error messages displayed for invalid input
        messages: {
            minColVal: {
                required: "Please enter a minimum column value",
                number: "Please enter a valid number for the minimum column value",
                integer: "Please enter a non-decimal number for the minimum column value",
                min: "Please enter a value greater than or equal to -15 for the minimum column value",
                max: "Please enter a value less than or equal to 15 for the minimum column value"
            },
            maxColVal: {
                required: "Please enter a maximum column value",
                number: "Please enter a valid number for the maximum column value",
                integer: "Please enter a non-decimal number for the maximum column value",
                min: "Please enter a value greater than or equal to -15 for the maximum column value",
                max: "Please enter a value less than or equal to 15 for the maximum column value"
            },
            minRowVal: {
                required: "Please enter a minimum row value",
                number: "Please enter a valid number for the minimum row value",
                integer: "Please enter a non-decimal number for the minimum row value",
                min: "Please enter a value greater than or equal to -15 for the minimum row value",
                max: "Please enter a value less than or equal to 15 for the minimum row value"
            },
            maxRowVal: {
                required: "Please enter a maximum row value",
                number: "Please enter a valid number for the maximum row value",
                integer: "Please enter a non-decimal number for the maximum row value",
                min: "Please enter a value greater than or equal to -15 for the maximum row value",
                max: "Please enter a value less than or equal to 15 for the maximum row value"
            }
        }
    });

});

