var fileCount = 0;

window.jsPDF = window.jspdf.jsPDF;

var xDown = 0;
var yDown = 0;
var xUp = 0;
var yUp = 0;
var prevX = 0;
var prevY = 0;

var currentPos = [];

const triPoints = [69, 8, 19, 108, 119, 108];
const circPoints = [70, 177, 50];
const rectPoints = [12, 247, 132, 247, 132, 317, 12, 317];
const squarePoints = [25, 359, 125, 359, 125, 459, 25, 459];
const pentPoints = [75, 489, 140, 524, 107, 589, 42, 589, 10, 524];
const ellipsePoints = [75, 670, 65, 45];

const shapeMenu = [triPoints, rectPoints, pentPoints, circPoints, squarePoints, ellipsePoints];

var shapes = [];
var colors = [];
var defaultColor = "#00a8fc";
var selectedColor = "#000000";

var selectedShape = [];
var selectedShapeIndex = -1;

var clipBoard = [];

var rotAngle = Math.PI/6;
var scaleFactor = 1.1;
// var scaleFactorDown = 0.9;

var isDown = false;

var scaleMode = false;

var reader = new FileReader();

window.onload = function init() {
    var canvas = document.getElementById( "canvas" );

    canvas.addEventListener("mousedown", mouseDown);
    canvas.addEventListener("mouseup", mouseUp);
    canvas.addEventListener("mousemove", mouseMove);
    document.addEventListener("keydown", keyPressed);
    document.getElementById("load").addEventListener("change", loadFile);
    
    if (canvas.getContext) {
        var ctx = canvas.getContext("2d");

        drawInit(ctx);

        // console.log(shapes);
    }
    else {
        console.log("Failed to initialize canvas.");
    }
}

function printCoords() {
    console.log(selectedShape);
}

function drawInit(ctx) {
    drawMenuSpace();

    for (var i = 0; i < shapeMenu.length; i++) {
        drawShape(ctx, shapeMenu[i], false, false, defaultColor);
    }
}

function drawMenuSpace() {
    var canvas = document.getElementById( "canvas" );
    var ctx = canvas.getContext("2d");

    // ctx.fillStyle = "#989a9c"; // gray
    ctx.fillStyle = "#d4d3d2"; // gray
    ctx.beginPath();
    ctx.rect(0, 0, 145, canvas.height);
    ctx.closePath();
    ctx.fill();
    ctx.stroke();
}

function undo() {
    var canvas = document.getElementById( "canvas" );
    var ctx = canvas.getContext("2d");

    shapes.pop();

    clearCanvas();
    drawCurrentShapes(ctx);
}

function reset() {
    // need to add a confirm message if shapes.length is >= 1
    if (shapes.length >= 1) {
        if (!confirm("Are you sure you want to clear the canvas?")) {
            return;
        }
    }

    var canvas = document.getElementById( "canvas" );
    var ctx = canvas.getContext("2d");

    shapes = [];
    colors = [];
    selectedShape = [];
    selectedShapeIndex = -1;

    clearCanvas();
    drawInit(ctx);
}

function clearCanvas() {
    var canvas = document.getElementById( "canvas" );
    var ctx = canvas.getContext("2d");
    ctx.clearRect(0, 0, canvas.width, canvas.height);
}

function clearShape() {
    if (selectedShapeIndex == -1) {
        return;
    }

    shapes.splice(selectedShapeIndex, 1);
    colors.splice(selectedShapeIndex, 1);
    selectedShapeIndex = -1;

    var canvas = document.getElementById( "canvas" );
    var ctx = canvas.getContext("2d");

    clearCanvas();
    drawCurrentShapes(ctx);
}

function drawCurrentShapes(ctx) {
    drawInit(ctx);

    for (var i = 0; i < shapes.length; i++) {
        if (i == selectedShapeIndex) {
            drawShape(ctx, shapes[i], false, true, colors[i]); 
        }
        else {
            drawShape(ctx, shapes[i], false, false, colors[i]);
        }
    }
}

function mouseDown(event) {
    xDown = event.clientX;
	yDown = event.clientY;

    prevX = xDown;
    prevY = yDown;

    isDown = true;
}

function mouseUp(event) {
    xUp = event.clientX;
	yUp = event.clientY;

    isDown = false;

    var canvas = document.getElementById( "canvas" );
    var ctx = canvas.getContext("2d");

    var index = checkPoint(ctx);
    // console.log(index);
    if (index != -1) {  // point found in shape at index
        if (scaleMode) {

        }
        else {
            translateShape(ctx, shapes[index], [xDown, yDown], [xUp, yUp], index);
        }
    }
}

function mouseMove(event) {
	var x = event.clientX;
	var y = event.clientY;

	/*if(isDown) {
        var canvas = document.getElementById( "canvas" );
        var ctx = canvas.getContext("2d");

        var index = checkPoint(ctx);
        // console.log(index);
        if (index != -1) {  // point found in shape at index
            if (scaleMode) {

            }
            else {
                translateShape(ctx, shapes[index], [prevX, prevY], [x, y], index);
            }
        }
	}*/

	var coords = "X: "+ x + " Y: " + y;	
	document.getElementById("coordinates").innerHTML = coords;

    currentPos = [x, y];

    prevX = x;
    prevY = y;
}

function keyPressed(event) {
    /*if (event.key == 's') { 
        scaleMode = !scaleMode;
        console.log("scale mode", scaleMode);
    }*/

    // Ctrl+C pressed
    if ((event.ctrlKey || event.metaKey) && event.keyCode == 67) {
        console.log("ctr-c");
        if (selectedShapeIndex != -1) {
            clipBoard = selectedShape;
        } 
    }

     // Ctrl+V pressed
     if ((event.ctrlKey || event.metaKey) && event.keyCode == 86) {
        var canvas = document.getElementById( "canvas" );
        var ctx = canvas.getContext("2d");
        console.log("ctr-v")
        if (clipBoard != []) {
            // drawShape(ctx, clipBoard, true, false);
            shapes.push(clipBoard);
            translateShape(ctx, clipBoard, [clipBoard[0], clipBoard[1]], [currentPos[0], currentPos[1]], shapes.length - 1);
        }
    }
}

function copy() {
    if (selectedShapeIndex != -1) {
        clipBoard = selectedShape;
    } 
}

function paste() {
    var canvas = document.getElementById( "canvas" );
    var ctx = canvas.getContext("2d");

    if (clipBoard != []) {
        shapes.push(clipBoard);
        translateShape(ctx, clipBoard, [clipBoard[0], clipBoard[1]], [250, 100], shapes.length - 1);
    }
}

function checkPoint(ctx) {
    var p = [xDown, yDown];
    // var p = [prevX, prevY];

    for (var i = 0; i < shapeMenu.length; i++) {
        if (shapeMenu[i].length == 3) {    // shape is a circle
            var xVals = [shapeMenu[i][0], shapeMenu[i][0] + shapeMenu[i][2], shapeMenu[i][0] - shapeMenu[i][2]];
            var yVals = [shapeMenu[i][1], shapeMenu[i][1] + shapeMenu[i][2], shapeMenu[i][1] - shapeMenu[i][2]];
        }
        else if (shapeMenu[i].length == 4) { // shape is an ellipse
            var xVals = [shapeMenu[i][0], shapeMenu[i][0] + shapeMenu[i][2], shapeMenu[i][0] - shapeMenu[i][2]];
            var yVals = [shapeMenu[i][1], shapeMenu[i][1] + shapeMenu[i][3], shapeMenu[i][1] - shapeMenu[i][3]];
        }
        else {
            var [xVals, yVals] = calcXYValues(shapeMenu[i]);
        }

        const xMin = Math.min(...xVals);
        const xMax = Math.max(...xVals);

        const yMin = Math.min(...yVals);
        const yMax = Math.max(...yVals);

        if (!(p[0] < xMin || p[0] > xMax || p[1] < yMin || p[1] > yMax)) {     // point found in shape at index
            var index = drawShape(ctx, shapeMenu[i], true, true, defaultColor) - 1;
            translateShape(ctx, shapes[index], p, [xUp, yUp], index);
        }
    }

    for (var i = 0; i < shapes.length; i++) {
        if (shapes[i].length == 3) {    // shape is a circle
            var xVals = [shapes[i][0], shapes[i][0] + shapes[i][2], shapes[i][0] - shapes[i][2]];
            var yVals = [shapes[i][1], shapes[i][1] + shapes[i][2], shapes[i][1] - shapes[i][2]];
        }
        else if (shapes[i].length == 4) { // shape is an ellipse
            var xVals = [shapes[i][0], shapes[i][0] + shapes[i][2], shapes[i][0] - shapes[i][2]];
            var yVals = [shapes[i][1], shapes[i][1] + shapes[i][3], shapes[i][1] - shapes[i][3]];
        }
        else {
            var [xVals, yVals] = calcXYValues(shapes[i]);
        }

        const xMin = Math.min(...xVals);
        const xMax = Math.max(...xVals);

        const yMin = Math.min(...yVals);
        const yMax = Math.max(...yVals);

        if (!(p[0] < xMin || p[0] > xMax || p[1] < yMin || p[1] > yMax)) {     // point found in shape at index
            return i;
        }
    }

    return -1;
}

function calcXYValues(points) {
    var xVals = [];
    var yVals = [];

    for (var i = 0; i < points.length; i++) {
        if (i % 2 == 0) {
            xVals.push(points[i]);
        }
        else {
            yVals.push(points[i]);
        }
    }

    return [xVals, yVals];
}

function drawShape(ctx, points, newFlag, selectFlag, color) {
    ctx.fillStyle = color;
    ctx.beginPath();

    if (points.length == 3) {   // shape is a circle
        ctx.arc(points[0], points[1], points[2], 0, Math.PI * 2);
    }
    else if (points.length == 4) {  // shape is an ellipse
        ctx.ellipse(points[0], points[1], points[2], points[3], Math.PI, 0, 2 * Math.PI);
    }
    else {
        const [xVals, yVals] = calcXYValues(points);

        // console.log("xVals: " + xVals + "\nyVals: " + yVals);

        ctx.moveTo(xVals[0], yVals[0]);
        for (var i = 1; i < yVals.length; i++) {
            ctx.lineTo(xVals[i], yVals[i]);
        }
    }
    ctx.closePath();
    ctx.fill();

    if (selectFlag) {
        ctx.stroke();
    }

    if (newFlag) {
        shapes.push(points);
        colors.push(color);
    }

    return shapes.length;
}

function translatePoint(x, y, t) {
    return [x + t[0], y + t[1]];
}

function translateShape(ctx, points, startP, endP, index) {
    if (points.length == 3 || points.length == 4) {   // shape is a circle or ellipse
        var xVals = [points[0]];
        var yVals = [points[1]];
    }
    else {
        var [xVals, yVals] = calcXYValues(points);
    }

    const diff = [endP[0] - startP[0], endP[1] - startP[1]];
    
    var newPoints = [];

    for (var i = 0; i < yVals.length; i++) {
        var p = translatePoint(xVals[i], yVals[i], diff);
        newPoints.push(p[0]);
        newPoints.push(p[1]);
    }

    if (points.length == 3) {   // shape is a circle
        newPoints.push(points[2]);
    }
    else if (points.length == 4) {
        newPoints.push(points[2]);
        newPoints.push(points[3]);
    }

    shapes[index] = newPoints;

    selectedShape = shapes[index];
    selectedShapeIndex = index;

    clearCanvas();
    drawCurrentShapes(ctx);

    // console.log(shapes);
}

function findMidpoint(points) {
    var [xVals, yVals] = calcXYValues(points);

    if (points.length == 4) {
        var cx = points[0];
        var cy = points[1];
    }
    else if (points.length == 6) {   // triangle
        var cx = (xVals[0] + xVals[1] + xVals[2]) / 3;
        var cy = (yVals[0] + yVals[1] + yVals[2]) / 3;
    }
    else if (points.length == 8) {  // rectangle/square
        var tx1 = (xVals[0] + xVals[1] + xVals[3]) / 3;
        var ty1 = (yVals[0] + yVals[1] + yVals[3]) / 3;
    
        var tx2 = (xVals[1] + xVals[2] + xVals[3]) / 3;
        var ty2 = (yVals[1] + yVals[2] + yVals[3]) / 3;
    
        var cx = (tx1 + tx2) / 2;
        var cy = (ty1 + ty2) / 2;
    }
    else if (points.length == 10) { // pentagon
        var x = [xVals[0], xVals[1], xVals[2], xVals[3], xVals[4], xVals[0]];
        var y = [yVals[0], yVals[1], yVals[2], yVals[3], yVals[4], yVals[0]];

        var A = 0;
        for (var i = 0; i < 5; i++) {
            A += (x[i] * y[i+1]) - (x[i+1] * y[i]);
        }
        A /= 2;
        var mult = 1 / (A * 6);
    
        var cy = 0;
        for(var i = 0; i < 5; i++) {
            cy += (y[i] + y[i+1]) * ((x[i] * y[i+1]) - (x[i+1] * y[i]));
        }
        cy *= mult;
        var cx = xVals[0];
    }

    return [cx, cy];
}

function matrixCalc(a, b, c, d, x, y, cx, cy) {
    const tx = x - cx;
    const ty = y - cy;

    const rx = (a * tx) + (b * ty);
    const ry = (c * tx) + (d * ty);

    const x1 = rx + cx;
    const y1 = ry + cy;

    return [x1, y1];
}

function rotatePoint(x, y, cx, cy, dir) {
    if (dir == "right") {
        var rotationMatrix = [Math.cos(rotAngle), -Math.sin(rotAngle),
                                Math.sin(rotAngle), Math.cos(rotAngle)];
    }
    else if (dir == "left") {
        var rotationMatrix = [Math.cos(rotAngle), Math.sin(rotAngle),
                                -Math.sin(rotAngle), Math.cos(rotAngle)];
    }

    const a = rotationMatrix[0];
    const b = rotationMatrix[1];
    const c = rotationMatrix[2];
    const d = rotationMatrix[3];

    return matrixCalc(a, b, c, d, x, y, cx, cy);
}

function rotateShape(ctx, points, dir, index) {
    // console.log(points, index);

    const c = findMidpoint(points);
    var newPoints = [];
    var [xVals, yVals] = calcXYValues(points);

    for (var i = 0; i < yVals.length; i++) {
        var p = rotatePoint(xVals[i], yVals[i], c[0], c[1], dir);
        newPoints.push(p[0]);
        newPoints.push(p[1]);
    }

    shapes[index] = newPoints;
    selectedShape = shapes[index];

    clearCanvas();
    drawCurrentShapes(ctx);
}

function rotate(dir) {
    if (selectedShapeIndex == -1 || selectedShape.length == 3 || selectedShape.length == 4) {   // cant figure out how to rotate an ellipse
        return;
    }

    var canvas = document.getElementById( "canvas" );
    var ctx = canvas.getContext("2d");

    rotateShape(ctx, selectedShape, dir, selectedShapeIndex);
}

function changeRotAngle() {
    var angle = document.getElementById("rotationAngle").value;

    if (angle == "30") {
        rotAngle = Math.PI/6;
    }
    else if (angle == "45") {
        rotAngle = Math.PI/4;
    }
    else if (angle == "60") {
        rotAngle = Math.PI/3;
    }
    else if (angle == "90") {
        rotAngle = Math.PI/2;
    }
}

function updateScaleFactor(factor) {
    scaleFactor = factor;
    
    if (factor == 1) {
        document.getElementById("sliderVal").innerHTML = "1.0";
    }
    else if (factor == 2) {
        document.getElementById("sliderVal").innerHTML = "2.0";
    }
    else {
        document.getElementById("sliderVal").innerHTML = factor;
    }
}

function scalePoint(x, y, cx, cy) {
    /*if (dir == "up") {
        var scalingMatrix = [scaleFactorUp, 0,
                                0, scaleFactorUp];
    }
    else if (dir == "down") {
        var scalingMatrix = [scaleFactorDown, 0,
                                0, scaleFactorDown];
    }*/

    var scalingMatrix = [scaleFactor, 0,
        0, scaleFactor];

    const a = scalingMatrix[0];
    const b = scalingMatrix[1];
    const c = scalingMatrix[2];
    const d = scalingMatrix[3];

    return matrixCalc(a, b, c, d, x, y, cx, cy);
}

function scaleShape(ctx, points, index) {
    // console.log(points, index);

    if (scaleFactor >= 1) {
        var dir = "up";
    }
    else {
        var dir = "down";
    }

    if (points.length == 3) {   // shape is a circle
        if (dir == "up") {
            shapes[index][2] += 5;
        }
        else if (dir == "down") {
            if (shapes[index][2] >= 10) {
                shapes[index][2] -= 5;
            }
        }
    }
    else if (points.length == 4) {   // shape is an ellipse
        if (dir == "up") {
            shapes[index][2] += 5;
            shapes[index][3] += 5;
        }
        else if (dir == "down") {
            if (shapes[index][2] >= 10 && shapes[index][3] >= 10) {
                shapes[index][2] -= 5;
                shapes[index][3] -= 5;
            }
        }
    }
    else {
        const c = findMidpoint(points);
        const [xVals, yVals] = calcXYValues(points);

        var newPoints = [];

        for (var i = 0; i < yVals.length; i++) {
            var p = scalePoint(xVals[i], yVals[i], c[0], c[1]);
            newPoints.push(p[0]);
            newPoints.push(p[1]);
        }

        shapes[index] = newPoints;
    }

    selectedShape = shapes[index];

    clearCanvas();
    drawCurrentShapes(ctx);
}

function scale() {
    if (selectedShapeIndex == -1) {
        return;
    }

    var canvas = document.getElementById( "canvas" );
    var ctx = canvas.getContext("2d");

    scaleShape(ctx, selectedShape, selectedShapeIndex);
}

function colorUpdate(col) {
    selectedColor = col;
}

function changeColor() {
    // var color = document.getElementById("colorChoice").value;
    var color = selectedColor;
    var canvas = document.getElementById( "canvas" );
    var ctx = canvas.getContext("2d");

    var points = selectedShape;

    clearShape();

    selectedShapeIndex = drawShape(ctx, points, true, true, color);
}

function exportCanvas() {
    var canvasElement = document.getElementById( "canvas" );

    var fileType = document.getElementById("exportFileType").value;
    var fileName = "download" + fileCount;
    fileCount++;

    if (fileType == "pdf") {
        var MIME_TYPE = "image/png";
        var imgURL = canvasElement.toDataURL(MIME_TYPE);

        var pdf = new jsPDF('1', 'px', [879, canvasElement.height]);

        width = pdf.internal.pageSize.getWidth();
        height = pdf.internal.pageSize.getHeight();

        pdf.addImage(imgURL, "PNG", -125, 0, width, height);
        pdf.save(fileName + ".pdf");
    }
    else if (fileType == "json") {
        // retrieve the canvas data
        var canvasContents = canvas.toDataURL(); // a data URL of the current canvas image
        var data = { image: canvasContents, date: Date.now() };
        var string = JSON.stringify(data);

        // create a blob object representing the data as a JSON string
        var file = new Blob([string], {
        type: 'application/json'
        });

        // trigger a click event on an <a> tag to open the file explorer
        var a = document.createElement('a');
        a.href = URL.createObjectURL(file);
        a.download = 'data.json';
        document.body.appendChild(a);
        a.click();
        document.body.removeChild(a);
    }
    else {
        var MIME_TYPE = "image/" + fileType;
        var imgURL = canvasElement.toDataURL(MIME_TYPE);

        var dlLink = document.createElement('a');
        dlLink.download = fileName;
        dlLink.href = imgURL;
        dlLink.dataset.downloadurl = [MIME_TYPE, dlLink.download, dlLink.href].join(':');

        document.body.appendChild(dlLink);
        dlLink.click();
        document.body.removeChild(dlLink);
    }
}

// event handler for the load button
/*document.getElementById("load").addEventListener("change", function () {
    if (this.files[0]) {
      // read the contents of the first file in the <input type="file">
      reader.readAsText(this.files[0]);
    }
});*/

function loadFile(event) {
    if (this.files[0]) {
        // read the contents of the first file in the <input type="file">
        reader.readAsText(this.files[0]);
    }
}
  
// this function executes when the contents of the file have been fetched
reader.onload = function () {
    var data = JSON.parse(reader.result);
    console.log(data);
    var image = new Image();
    image.onload = function () {
        var canvas = document.getElementById( "canvas" );
        var ctx = canvas.getContext("2d");
        ctx.clearRect(0, 0, canvas.width, canvas.height);
        ctx.drawImage(image, 0, 0); // draw the new image to the screen
    }
    image.src = data.image; // data.image contains the data URL
};