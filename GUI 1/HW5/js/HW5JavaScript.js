/*
File: js/HW5JavaScript.js
GUI Assignment 5: Implementing a Bit of Scrabble with Drag-and-Drop

Peyton Somerville
12/4/2021
*/

// associative array provided by Professor Heines
var ScrabbleTiles = [] ;
ScrabbleTiles["A"] = { "value" : 1,  "original-distribution" : 9,  "number-remaining" : 9  } ;
ScrabbleTiles["B"] = { "value" : 3,  "original-distribution" : 2,  "number-remaining" : 2  } ;
ScrabbleTiles["C"] = { "value" : 3,  "original-distribution" : 2,  "number-remaining" : 2  } ;
ScrabbleTiles["D"] = { "value" : 2,  "original-distribution" : 4,  "number-remaining" : 4  } ;
ScrabbleTiles["E"] = { "value" : 1,  "original-distribution" : 12, "number-remaining" : 12 } ;
ScrabbleTiles["F"] = { "value" : 4,  "original-distribution" : 2,  "number-remaining" : 2  } ;
ScrabbleTiles["G"] = { "value" : 2,  "original-distribution" : 3,  "number-remaining" : 3  } ;
ScrabbleTiles["H"] = { "value" : 4,  "original-distribution" : 2,  "number-remaining" : 2  } ;
ScrabbleTiles["I"] = { "value" : 1,  "original-distribution" : 9,  "number-remaining" : 9  } ;
ScrabbleTiles["J"] = { "value" : 8,  "original-distribution" : 1,  "number-remaining" : 1  } ;
ScrabbleTiles["K"] = { "value" : 5,  "original-distribution" : 1,  "number-remaining" : 1  } ;
ScrabbleTiles["L"] = { "value" : 1,  "original-distribution" : 4,  "number-remaining" : 4  } ;
ScrabbleTiles["M"] = { "value" : 3,  "original-distribution" : 2,  "number-remaining" : 2  } ;
ScrabbleTiles["N"] = { "value" : 1,  "original-distribution" : 6,  "number-remaining" : 6  } ;
ScrabbleTiles["O"] = { "value" : 1,  "original-distribution" : 8,  "number-remaining" : 8  } ;
ScrabbleTiles["P"] = { "value" : 3,  "original-distribution" : 2,  "number-remaining" : 2  } ;
ScrabbleTiles["Q"] = { "value" : 10, "original-distribution" : 1,  "number-remaining" : 1  } ;
ScrabbleTiles["R"] = { "value" : 1,  "original-distribution" : 6,  "number-remaining" : 6  } ;
ScrabbleTiles["S"] = { "value" : 1,  "original-distribution" : 4,  "number-remaining" : 4  } ;
ScrabbleTiles["T"] = { "value" : 1,  "original-distribution" : 6,  "number-remaining" : 6  } ;
ScrabbleTiles["U"] = { "value" : 1,  "original-distribution" : 4,  "number-remaining" : 4  } ;
ScrabbleTiles["V"] = { "value" : 4,  "original-distribution" : 2,  "number-remaining" : 2  } ;
ScrabbleTiles["W"] = { "value" : 4,  "original-distribution" : 2,  "number-remaining" : 2  } ;
ScrabbleTiles["X"] = { "value" : 8,  "original-distribution" : 1,  "number-remaining" : 1  } ;
ScrabbleTiles["Y"] = { "value" : 4,  "original-distribution" : 2,  "number-remaining" : 2  } ;
ScrabbleTiles["Z"] = { "value" : 10, "original-distribution" : 1,  "number-remaining" : 1  } ;
ScrabbleTiles["_"] = { "value" : 0,  "original-distribution" : 2,  "number-remaining" : 2  } ;

var totalScore = 0;

// called when page loads to set up starting tile rack
$(function() {
    setup();
});

// build HTML for the starting tile rack
function setup() {
    var toMakeDroppable = ["1boardSquare", "2bonusSquare", "3boardSquare", "4boardSquare", "5boardSquare", "6bonusSquare", "7boardSquare", "exchangeTile", "tileRack"];
    var letter;
    var tileRackHTML;
    for(var i = 0; i < 7; i++) {
        letter = getRandomLetter();

        tileRackHTML = $("<img id=\"" + letter + "\" class=\"draggable\" src=\"img/tiles/Scrabble_Tile_" + letter + ".jpg\">");
        $("#tileRack").append(tileRackHTML);

        // make all the tiles draggable
        makeDraggable(tileRackHTML);

        // make all the squares droppable
        makeDroppable(toMakeDroppable[i]);
    }

    // make exchange box and tile rack droppable
    makeDroppableExchange(toMakeDroppable[7]);
    makeDroppableRack(toMakeDroppable[8]);

    displayTilesRemaining();
}

function getRandomLetter() {
    var tiles = "ABCDEFGHIJKLMNOPQRSTUVWXYZ_";
    var randomNum;
    var letter;
    do {
        randomNum = Math.floor(Math.random() * 27);
        letter = tiles[randomNum];
    } while(ScrabbleTiles[letter]["number-remaining"] == 0);

    ScrabbleTiles[letter]["number-remaining"] -= 1;

    return letter;
}

function submitWord() {
    // see which squares have tiles in them
    var activeSquares = document.getElementsByClassName("active_square");
    var activeSquareIDs = [];
    for (var i = 0; i < activeSquares.length; i++) {
        activeSquareIDs[i] = activeSquares[i].id;
    }
    // console.log(activeSquareIDs);
    gap = checkGap(activeSquareIDs);

    if (gap == true) {
        console.log("There is a gap.");
        $("#errorMessage").html("There is a gap in your word.")
        return;
    }
    else {
        $("#errorMessage").html("")
    }

    // get the ids of all the tiles that are being used on the board
    var activeTiles = document.getElementsByClassName("in_droppable_object");
    var activeTileIDs = [];
    for (var i = 0; i < activeTiles.length; i++) {
        activeTileIDs[i] = activeTiles[i].id;
    }
    // console.log(activeTileIDs);

    // find out how many bonus squares are being used
    var activeBonus = document.getElementsByClassName("active_bonus");
    var activeBonusIDs = [];
    for(var i = 0; i < activeBonus.length; i++) {
        activeBonusIDs[i] = activeBonus[i].id;
    }

    // adjust the multiplier based on the bonus squares
    var multiplier = 1;
    if (activeBonus.length == 1) {
        multiplier = 2;
        $("#" + activeBonusIDs[0]).removeClass("active_bonus");
    }
    else if (activeBonus.length == 2) {
        multiplier = 4;
        $("#" + activeBonusIDs[0]).removeClass("active_bonus");
        $("#" + activeBonusIDs[1]).removeClass("active_bonus");
    }

    // calcualte score based on tile values and update square class to show not active
    var score = 0;
    for (var i = 0; i < activeTileIDs.length; i++) {
        score += ScrabbleTiles[activeTileIDs[i]]["value"];

        $("#" + activeSquareIDs[i]).removeClass("active_square");
    }

    // remove all of the tiles that were used
    $(".in_droppable_object").remove();

    score *= multiplier;
    // console.log("score = " + score);

    totalScore += score;
    $("#score").html("Score = " + totalScore + " (+" + score + ")");

    // fill up the tile rack based on the remaining tiles
    var remainingTiles = calcTilesRemaining();
    if (activeTileIDs.length > remainingTiles) {
        for (var i = 0; i < remainingTiles; i++) {
            letter = getRandomLetter();

            tileRackHTML = $("<img id=\"" + letter + "\" class=\"draggable\" src=\"img/tiles/Scrabble_Tile_" + letter + ".jpg\">");
            $("#tileRack").append(tileRackHTML);

            // make the new tiles draggable
            makeDraggable(tileRackHTML);
        }
    }
    else {
        for (var i = 0; i < activeTileIDs.length; i++) {
            letter = getRandomLetter();

            tileRackHTML = $("<img id=\"" + letter + "\" class=\"draggable\" src=\"img/tiles/Scrabble_Tile_" + letter + ".jpg\">");
            $("#tileRack").append(tileRackHTML);

            // make the new tiles draggable
            makeDraggable(tileRackHTML);
        }
    }

    displayTilesRemaining();

    // console.log("Remaining tiles = " + remainingTiles);
}

function checkGap(activeSquareIDs) {
    var idNums = [];
    // get number values from the square ids
    for (var i = 0; i < activeSquareIDs.length; i++) {
        idNums[i] = parseInt(activeSquareIDs[i]);
    }
    // console.log(idNums);

    for (var i = 1; i < idNums.length; i++) {
        if (idNums[i] - idNums[i-1] != 1) {
            // this means there is a gap
            return true;
        }
    }

    return false;
}

function makeDraggable(tile) {
    // makes the tile draggable objects
    tile.draggable({
        // make the currently dragged object show on top of other objects
        stack: ".draggable",

        // makes tile go back to original position if not dropped in valid droppable object
        revert: "invalid"
    });
}

function makeDroppable(square) {
    // makes board square droppable objects
    $("#" + square).droppable({
        // triggered when a tile gets dropped into a square
        drop: function(event, ui) {
            // console.log("Score = " + ScrabbleTiles[tileID]["value"]);
            var squareIDin = $(this).attr("id");
            if (squareIDin == "2bonusSquare" || squareIDin == "6bonusSquare") {
                $(this).addClass("active_bonus");
            }

            if (squareIDin != "exchangeTile") {
                $(this).addClass("active_square");
            }

            // updates class of tile to show it is currently in a square
            ui.draggable.addClass("in_droppable_object");

            // makes dropped tiles go to the center of the square
            // code from: https://stackoverflow.com/questions/26746823/jquery-ui-drag-and-drop-snap-to-center
            var $this = $(this);
            ui.draggable.position({
                my: "center",
                at: "center",
                of: $this,
                using: function(pos) {
                    $(this).animate(pos, 200, "linear");
                }
            });
            
            // this part handles swapping tiles
            var tileID = ui.draggable.attr("id");
            if (squareIDin == "exchangeTile") {
                $("#" + tileID).addClass("remove");
                $(".remove").remove();
                ScrabbleTiles[tileID]["number-remaining"] += 1;

                letter = getRandomLetter();
                tileHTML = $("<img id=\"" + letter + "\" class=\"draggable\" src=\"img/tiles/Scrabble_Tile_" + letter + ".jpg\">");
                $("#tileRack").append(tileHTML);
                makeDraggable(tileHTML);
            }
        },
        // triggered when a tile gets moved out of a square
        out: function(event, ui) {
            var squareIDout = $(this).attr("id");
            if (squareIDout == "2bonusSquare" || squareIDout == "6bonusSquare") {
                $(this).removeClass("active_bonus");
            }

            // update class of square to show there is no longer a tile in it
            $(this).removeClass("active_square");

            // updates class of tile to show it is no longer in a square
            ui.draggable.removeClass("in_droppable_object");
        },

        // adds class to highlight square when hovering over it
        hoverClass: "drop-hover"
    });
}

function makeDroppableRack(square) {
    // makes board square droppable objects
    $("#" + square).droppable({
        // adds class to highlight square when hovering over it
        hoverClass: "drop-hover-rack"
    });
}

function makeDroppableExchange(square) {
    // makes board square droppable objects
    $("#" + square).droppable({
        // triggered when a tile gets dropped into a square
        drop: function(event, ui) {
            // this part handles swapping tiles
            var tileID = ui.draggable.attr("id");
            var squareIDin = $(this).attr("id");
            if (squareIDin == "exchangeTile") {
                $("#" + tileID).addClass("remove");
                $(".remove").remove();
                ScrabbleTiles[tileID]["number-remaining"] += 1;

                letter = getRandomLetter();
                tileHTML = $("<img id=\"" + letter + "\" class=\"draggable\" src=\"img/tiles/Scrabble_Tile_" + letter + ".jpg\">");
                $("#tileRack").append(tileHTML);
                makeDraggable(tileHTML);
            }
        },

        // adds class to highlight square when hovering over it
        hoverClass: "drop-hover-exchange"
    });
}

function calcTilesRemaining() {
    var tiles = "ABCDEFGHIJKLMNOPQRSTUVWXYZ_";
    var letter;
    var tilesRemaining = 0;
    for (var i = 0; i < 27; i++) {
        letter = tiles[i];
        tilesRemaining += ScrabbleTiles[letter]["number-remaining"];
    }

    // console.log("Remaining tiles = " + tilesRemaining);
    return tilesRemaining;
}

function displayTilesRemaining() {
    var remainingTiles = calcTilesRemaining();
    $("#tilesRemaining").html("Remaining Tiles = " + remainingTiles);
}

function resetGame() {
    totalScore = 0;
     $("#score").html("Score = " + totalScore);

    // remove all tiles
    $(".draggable").remove();

    resetTileCount();

    setup();
}

// changes the associative array back to its original state
function resetTileCount() {
    var tiles = "ABCDEFGHIJKLMNOPQRSTUVWXYZ_";
    var letter; 

    for (var i = 0; i < 27; i++) {
        letter = tiles[i];
        ScrabbleTiles[letter]["number-remaining"] = ScrabbleTiles[letter]["original-distribution"];
    }
}

