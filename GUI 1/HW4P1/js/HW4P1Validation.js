/*
File: js/HW4P1Validation.js
GUI Assignment 4: Using the jQuery Plugin/UI with Your Dynamic Table 
Part 1: Validation Plugin 

This webpage creates a dynamic multiplication table based on user input using HTML, CSS, and JavaScript.
The user input is now validated with jQeury.

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
                min: -200,
                max: 200
            },
            maxColVal: {
                required: true,
                number: true,
                integer: true,      
                min: -200,
                max: 200
            },
            minRowVal: {
                required: true,
                number: true,
                integer: true,      
                min: -200,
                max: 200
            },
            maxRowVal: {
                required: true,
                number: true,
                integer: true,      
                min: -200,
                max: 200
            }
        },

        // error messages displayed for invalid input
        messages: {
            minColVal: {
                required: "Please enter a value for the minimum column value",
                number: "Please enter a valid number for the minimum column value",
                integer: "Please enter a non-decimal number for the minimum column value",
                min: "Please enter a value greater than or equal to -200 for the minimum column value",
                max: "Please enter a value less than or equal to 200 for the minimum column value"
            },
            maxColVal: {
                required: "Please enter a value for the maximum column value",
                number: "Please enter a valid number for the maximum column value",
                integer: "Please enter a non-decimal number for the maximum column value",
                min: "Please enter a value greater than or equal to -200 for the maximum column value",
                max: "Please enter a value less than or equal to 200 for the maximum column value"
            },
            minRowVal: {
                required: "Please enter a value for the minimum row value",
                number: "Please enter a valid number for the minimum row value",
                integer: "Please enter a non-decimal number for the minimum row value",
                min: "Please enter a value greater than or equal to -200 for the minimum row value",
                max: "Please enter a value less than or equal to 200 for the minimum row value"
            },
            maxRowVal: {
                required: "Please enter a value for the maximum row value",
                number: "Please enter a valid number for the maximum row value",
                integer: "Please enter a non-decimal number for the maximum row value",
                min: "Please enter a value greater than or equal to -200 for the maximum row value",
                max: "Please enter a value less than or equal to 200 for the maximum row value"
            }
        }
    });

});