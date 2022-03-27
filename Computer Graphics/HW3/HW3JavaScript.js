var rotAngle = Math.PI/6;
var scaleFactorUp = 1.1;
var scaleFactorDown = 0.9;

var triPoints = [250, 20, 200, 120, 300, 120];
var circleInfo = [400, 75, 50];
var rectPoints = [100, 200, 220, 200, 220, 270, 100, 270];
var linePoints = [300, 235, 375, 235];
var pentPoints = [100, 20, 165, 55, 132, 120, 67, 120, 35, 55];

var mPos = [0, 0];

var flag = false;
var tempPoint = [0, 0];

window.onload = function init() {
    var canvas = document.getElementById( "canvas" );
    canvas.addEventListener("click", checkMouseInShape);
    canvas.addEventListener("mousemove", updateCurrentMousePos);
    
    if (canvas.getContext) {
        var ctx = canvas.getContext("2d");
        drawInitShapes(ctx);
    }
    else {
        console.log("Failed to initialize canvas.");
    }
}

function drawInitShapes(ctx) {
    var canvas = document.getElementById( "canvas" );
    var ctx = canvas.getContext("2d");

    var shape = document.getElementById("shapeSelect").value;
    switch (shape) {
        case "pentagon":
            drawPentagon(ctx, 100, 20, 165, 55, 132, 120, 67, 120, 35, 55);
            break;
        
        case "triangle":
            drawTriangle(ctx, 250, 20, 200, 120, 300, 120);
            break;
        
        case "circle":
            drawCircle(ctx, 400, 75, 50);
            break;
        
        case "rectangle":
            drawRectangle(ctx, 100, 200, 220, 200, 220, 270, 100, 270);
            break;
        
        case "line":
            drawLine(ctx, 300, 235, 375, 235);
            break;
        
        default:
            console.log("Something went wrong while selecting a shape...");
            break;
    }
}

function reset() {
    var canvas = document.getElementById( "canvas" );
    var ctx = canvas.getContext("2d");

    ctx.clearRect(0, 0, canvas.width, canvas.height);

    triPoints = [250, 20, 200, 120, 300, 120];
    circleInfo = [400, 75, 50];
    rectPoints = [100, 200, 220, 200, 220, 270, 100, 270];
    linePoints = [300, 235, 375, 235];
    pentPoints = [100, 20, 165, 55, 132, 120, 67, 120, 35, 55];

    document.getElementById("selected").innerHTML = "No shape grabbed";
    document.getElementById("selected").style.color = "#000000";

    drawInitShapes(ctx);
}

function updateCurrentMousePos(event) {
    mPos[0] = event.clientX;
    mPos[1] = event.clientY;
}

function checkMouseInShape(event) {
    // console.log(event.clientX + " " + event.clientY)

    const x = event.clientX;
    const y = event.clientY;

    var canvas = document.getElementById( "canvas" );
    var ctx = canvas.getContext("2d");

    var shape = document.getElementById("shapeSelect").value;
    switch (shape) {
        case "pentagon":
            if (flag == false) {
                if (checkPointInShape([pentPoints[0], pentPoints[2], pentPoints[4], pentPoints[6], pentPoints[8]], [pentPoints[1], pentPoints[3], pentPoints[5], pentPoints[7], pentPoints[9]], [x, y])) {
                    //console.log("pentagon selected");

                    document.getElementById("selected").innerHTML = "Pentagon grabbed";
                    document.getElementById("selected").style.color = "#39e6dd";

                    flag = true;
                    tempPoint = [x, y];
                }
                else {
                    //console.log("not in rectangle")
                }
            }
            else {
                flag = false;
                translatePentagon(ctx, pentPoints[0], pentPoints[1], pentPoints[2], pentPoints[3], pentPoints[4], pentPoints[5],
                    pentPoints[6], pentPoints[7], pentPoints[8], pentPoints[9], [x, y], tempPoint);

                document.getElementById("selected").innerHTML = "Pentagon moved";
                document.getElementById("selected").style.color = "#39e6dd";
            }
            break;
        
        case "triangle":
            if (flag == false) {
                if (checkPointInShape([triPoints[0], triPoints[2], triPoints[4]], [triPoints[1], triPoints[3], triPoints[5]], [x, y])) {
                    //console.log("triangle selected");

                    document.getElementById("selected").innerHTML = "Triangle grabbed";
                    document.getElementById("selected").style.color = "#ed220c";

                    flag = true;
                    tempPoint = [x, y];
                }
                else {
                    //console.log("not in triangle")
                }
            }
            else {
                flag = false;
                translateTriangle(ctx, triPoints[0], triPoints[1], triPoints[2], triPoints[3], triPoints[4], triPoints[5], [x, y], tempPoint);

                document.getElementById("selected").innerHTML = "Triangle moved";
                document.getElementById("selected").style.color = "#ed220c";
            }
            break;
        
        case "circle":
            if (flag == false) {
                if (checkPointInShape([circleInfo[0], circleInfo[0] + circleInfo[2], circleInfo[0] - circleInfo[2]], 
                        [circleInfo[1], circleInfo[1] + circleInfo[2], circleInfo[1] - circleInfo[2]], [x, y])) {
                    //console.log("circle selected");

                    document.getElementById("selected").innerHTML = "Cirlce grabbed";
                    document.getElementById("selected").style.color = "#0c10ed";

                    flag = true;
                    tempPoint = [x, y];
                }
                else {
                    //console.log("not in circle")
                }
            }
            else {
                flag = false;
                translateCircle(ctx, circleInfo[0], circleInfo[1], circleInfo[2], [x, y], tempPoint);

                document.getElementById("selected").innerHTML = "Circle moved";
                document.getElementById("selected").style.color = "#0c10ed";
            }
            break;
        
        case "rectangle":
            if (flag == false) {
                if (checkPointInShape([rectPoints[0], rectPoints[2], rectPoints[4], rectPoints[6]], [rectPoints[1], rectPoints[3], rectPoints[5], rectPoints[7]], [x, y])) {
                    //console.log("rectangle selected");

                    document.getElementById("selected").innerHTML = "Rectangle grabbed";
                    document.getElementById("selected").style.color = "#33d431";

                    flag = true;
                    tempPoint = [x, y];
                }
                else {
                    //console.log("not in rectangle")
                }
            }
            else {
                flag = false;
                translateRectangle(ctx, rectPoints[0], rectPoints[1], rectPoints[2], rectPoints[3], rectPoints[4], rectPoints[5], rectPoints[6], rectPoints[7], [x, y], tempPoint);

                document.getElementById("selected").innerHTML = "Rectangle moved";
                document.getElementById("selected").style.color = "#33d431";
            }
            break;
        
        case "line":
            if (flag == false) {
                if (checkPointInShape([linePoints[0] + 15, linePoints[0] - 15, linePoints[2] + 15, linePoints[2] - 15], 
                        [linePoints[1] + 15, linePoints[1] - 15, linePoints[3] + 15, linePoints[3] - 15], [x, y])) {
                    //console.log("line selected");

                    document.getElementById("selected").innerHTML = "Line grabbed";
                    document.getElementById("selected").style.color = "#ff8c00";

                    flag = true;
                    tempPoint = [x, y];
                }
                else {
                    //console.log("not in line")
                }
            }
            else {
                flag = false;
                translateLine(ctx, linePoints[0], linePoints[1], linePoints[2], linePoints[3], [x, y], tempPoint);

                document.getElementById("selected").innerHTML = "Line moved";
                document.getElementById("selected").style.color = "#ff8c00";
            }
            break;
        
        default:
            console.log("Something went wrong while selecting a shape...");
            break;
    }
}

function checkPointInShape(xVals, yVals, p) {
    const xMin = Math.min(...xVals);
    const xMax = Math.max(...xVals);

    const yMin = Math.min(...yVals);
    const yMax = Math.max(...yVals);

    if (p[0] < xMin || p[0] > xMax || p[1] < yMin || p[1] > yMax) {
        return false;
    }
    else {
        return true;
    }
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

function rotate(dir) {
    var canvas = document.getElementById( "canvas" );
    var ctx = canvas.getContext("2d");

    var shape = document.getElementById("shapeSelect").value;
    switch (shape) {
        case "pentagon":
            if (dir == "right") {
                rotatePentagon(ctx, pentPoints[0], pentPoints[1], pentPoints[2], pentPoints[3], pentPoints[4], pentPoints[5],
                    pentPoints[6], pentPoints[7], pentPoints[8], pentPoints[9], "right");
            }

            else if (dir == "left") {
                rotatePentagon(ctx, pentPoints[0], pentPoints[1], pentPoints[2], pentPoints[3], pentPoints[4], pentPoints[5],
                    pentPoints[6], pentPoints[7], pentPoints[8], pentPoints[9], "left");
            }
            break;
        
        case "triangle":
            if (dir == "right") {
                rotateTriangle(ctx, triPoints[0], triPoints[1], triPoints[2], triPoints[3], triPoints[4], triPoints[5], "right");
            }

            else if (dir == "left") {
                rotateTriangle(ctx, triPoints[0], triPoints[1], triPoints[2], triPoints[3], triPoints[4], triPoints[5], "left");
            }
            break;
        
        case "circle":
            // do nothing
            break;
        
        case "rectangle":
            if (dir == "right") {
                rotateRectangle(ctx, rectPoints[0], rectPoints[1], rectPoints[2], rectPoints[3], rectPoints[4], rectPoints[5], rectPoints[6], rectPoints[7], "right");
            }

            else if (dir == "left") {
                rotateRectangle(ctx, rectPoints[0], rectPoints[1], rectPoints[2], rectPoints[3], rectPoints[4], rectPoints[5], rectPoints[6], rectPoints[7], "left");
            }
            break;
        
        case "line":
            if (dir == "right") {
                rotateLine(ctx, linePoints[0], linePoints[1], linePoints[2], linePoints[3], "right");
            }

            else if (dir == "left") {
                rotateLine(ctx, linePoints[0], linePoints[1], linePoints[2], linePoints[3], "left");
            }
            break;
        
        default:
            console.log("Something went wrong while selecting a shape...");
            break;
    }
}

function scalePoint(x, y, cx, cy, dir) {
    if (dir == "up") {
        var scalingMatrix = [scaleFactorUp, 0,
                                0, scaleFactorUp];
    }
    else if (dir == "down") {
        var scalingMatrix = [scaleFactorDown, 0,
                                0, scaleFactorDown];
    }

    const a = scalingMatrix[0];
    const b = scalingMatrix[1];
    const c = scalingMatrix[2];
    const d = scalingMatrix[3];

    return matrixCalc(a, b, c, d, x, y, cx, cy);
}

function scale(dir) {
    var canvas = document.getElementById( "canvas" );
    var ctx = canvas.getContext("2d");

    var shape = document.getElementById("shapeSelect").value;
    switch (shape) {
        case "pentagon":
            if (dir == "up") {
                scalePentagon(ctx, pentPoints[0], pentPoints[1], pentPoints[2], pentPoints[3], pentPoints[4], pentPoints[5],
                    pentPoints[6], pentPoints[7], pentPoints[8], pentPoints[9], "up");
            }

            else if (dir == "down") {
                scalePentagon(ctx, pentPoints[0], pentPoints[1], pentPoints[2], pentPoints[3], pentPoints[4], pentPoints[5],
                    pentPoints[6], pentPoints[7], pentPoints[8], pentPoints[9], "down");
            }
            break;
        
        case "triangle":
            if (dir == "up") {
                scaleTriangle(ctx, triPoints[0], triPoints[1], triPoints[2], triPoints[3], triPoints[4], triPoints[5], "up");
            }

            else if (dir == "down") {
                scaleTriangle(ctx, triPoints[0], triPoints[1], triPoints[2], triPoints[3], triPoints[4], triPoints[5], "down");
            }
            break;
        
        case "circle":
            if (dir == "up") {
                scaleCircle(ctx, circleInfo[0], circleInfo[1], circleInfo[2], "up");
            }

            else if (dir == "down") {
                scaleCircle(ctx, circleInfo[0], circleInfo[1], circleInfo[2], "down");
            }
            break;
        
        case "rectangle":
            if (dir == "up") {
                scaleRectangle(ctx, rectPoints[0], rectPoints[1], rectPoints[2], rectPoints[3], rectPoints[4], rectPoints[5], rectPoints[6], rectPoints[7], "up");
            }

            else if (dir == "down") {
                scaleRectangle(ctx, rectPoints[0], rectPoints[1], rectPoints[2], rectPoints[3], rectPoints[4], rectPoints[5], rectPoints[6], rectPoints[7], "down");
            }
            break;
        
        case "line":
            // do nothing
            break;
        
        default:
            console.log("Something went wrong while selecting a shape...");
            break;
    }
}

function drawTriangle(ctx, x1, y1, x2, y2, x3, y3) {
    ctx.fillStyle = "#ed220c"; // red
    ctx.beginPath();
    ctx.moveTo(x1, y1);
    ctx.lineTo(x2, y2);
    ctx.lineTo(x3, y3);
    ctx.closePath();
    ctx.fill();
}

// clearing a shape is redrawing the same shape with the color white
function clearTriangle(ctx, x1, y1, x2, y2, x3, y3) {
    ctx.fillStyle = "#ffffff"; // white
    ctx.strokeStyle = "#ffffff";

    for (var i = 0; i < 3; i++) {
        ctx.beginPath();
        ctx.moveTo(x1, y1);
        ctx.lineTo(x2, y2);
        ctx.lineTo(x3, y3);
        ctx.closePath();
        ctx.fill();
        ctx.stroke();
    }
}

function rotateTriangle(ctx, x1, y1, x2, y2, x3, y3, dir) {
    // erase current triangle
    clearTriangle(ctx, x1, y1, x2, y2, x3, y3);

    const c = findTriMidpoint(x1, y1, x2, y2, x3, y3);

    // rotate each point based on the midpoint
    if (dir == "right") {
        var p1 = rotatePoint(x1, y1, c[0], c[1], "right");
        var p2 = rotatePoint(x2, y2, c[0], c[1], "right");
        var p3 = rotatePoint(x3, y3, c[0], c[1], "right");
    }

    else if (dir == "left") {
        var p1 = rotatePoint(x1, y1, c[0], c[1], "left");
        var p2 = rotatePoint(x2, y2, c[0], c[1], "left");
        var p3 = rotatePoint(x3, y3, c[0], c[1], "left");
    }

    triPoints = [p1[0], p1[1], p2[0], p2[1], p3[0], p3[1]];

    // draw new triangle
    drawTriangle(ctx, p1[0], p1[1], p2[0], p2[1], p3[0], p3[1]);
}

function scaleTriangle(ctx, x1, y1, x2, y2, x3, y3, dir) {
    // erase current triangle
    clearTriangle(ctx, x1, y1, x2, y2, x3, y3);

    const c = findTriMidpoint(x1, y1, x2, y2, x3, y3);

    // scale each point based on the midpoint
    if (dir == "up") {
        var p1 = scalePoint(x1, y1, c[0], c[1], "up");
        var p2 = scalePoint(x2, y2, c[0], c[1], "up");
        var p3 = scalePoint(x3, y3, c[0], c[1], "up");
    }
    else if (dir == "down") {
        var p1 = scalePoint(x1, y1, c[0], c[1], "down");
        var p2 = scalePoint(x2, y2, c[0], c[1], "down");
        var p3 = scalePoint(x3, y3, c[0], c[1], "down");
    }

    triPoints = [p1[0], p1[1], p2[0], p2[1], p3[0], p3[1]];

    // draw new triangle
    drawTriangle(ctx, p1[0], p1[1], p2[0], p2[1], p3[0], p3[1]);
}

function translateTriangle(ctx, x1, y1, x2, y2, x3, y3, endP, startP) {
    clearTriangle(ctx, x1, y1, x2, y2, x3, y3);

    var diff = [endP[0] - startP[0], endP[1] - startP[1]];

    const p1 = translatePoint(x1, y1, diff);
    const p2 = translatePoint(x2, y2, diff);
    const p3 = translatePoint(x3, y3, diff);

    triPoints = [p1[0], p1[1], p2[0], p2[1], p3[0], p3[1]];

    drawTriangle(ctx, p1[0], p1[1], p2[0], p2[1], p3[0], p3[1]);
}

function translatePoint(x, y, t) {
    return [x + t[0], y + t[1]];
}

function findTriMidpoint(x1, y1, x2, y2, x3, y3) {
    const cx = (x1 + x2 + x3) / 3;
    const cy = (y1 + y2 + y3) / 3;

    return [cx, cy];
}

function drawCircle(ctx, x, y, r) {
    ctx.fillStyle = "#0c10ed"; // blue
    ctx.beginPath();
    ctx.arc(x, y, r, 0, Math.PI * 2);
    ctx.closePath();
    ctx.fill();
}

function clearCircle(ctx, x, y, r) {
    ctx.fillStyle = "#ffffff"; // white
    ctx.strokeStyle = "#ffffff";

    for (var i = 0; i < 3; i++) {
        ctx.beginPath();
        ctx.arc(x, y, r, 0, Math.PI * 2);
        ctx.closePath();
        ctx.fill();
        ctx.stroke();
    }
}

function scaleCircle(ctx, x, y, r, dir) {
    if (dir == "up") {
        clearCircle(ctx, x, y, r);
        circleInfo[2] += 5;
        r += 5;
    }

    else if (dir == "down") {
        if (circleInfo[2] >= 10) {
            clearCircle(ctx, x, y, r);
            circleInfo[2] -= 5;
            r -= 5;
        }
    }

    drawCircle(ctx, x, y, r);
}

function translateCircle(ctx, x, y, r, endP, startP) {
    clearCircle(ctx, x, y, r);

    var diff = [endP[0] - startP[0], endP[1] - startP[1]];

    const p = translatePoint(x, y, diff);

    circleInfo = [p[0], p[1], r];

    drawCircle(ctx, p[0], p[1], r);
}

function drawRectangle(ctx, x1, y1, x2, y2, x3, y3, x4, y4) {
    ctx.fillStyle = "#33d431";
    ctx.beginPath();
    ctx.moveTo(x1, y1);
    ctx.lineTo(x2, y2);
    ctx.lineTo(x3, y3);
    ctx.lineTo(x4, y4);
    ctx.closePath();
    ctx.fill();
}

function clearRectangle(ctx, x1, y1, x2, y2, x3, y3, x4, y4) {
    ctx.fillStyle = "#ffffff"; // white
    ctx.strokeStyle = "#ffffff";

    for (var i = 0; i < 3; i++) {
        ctx.beginPath();
        ctx.moveTo(x1, y1);
        ctx.lineTo(x2, y2);
        ctx.lineTo(x3, y3);
        ctx.lineTo(x4, y4);
        ctx.closePath();
        ctx.fill();
        ctx.stroke();
    }
}

function rotateRectangle(ctx, x1, y1, x2, y2, x3, y3, x4, y4, dir) {
    // erase current rectangle
    clearRectangle(ctx, x1, y1, x2, y2, x3, y3, x4, y4);

    const c = findRectMidpoint(x1, y1, x2, y2, x3, y3, x4, y4);

    // rotate each point based on the midpoint
    if (dir == "right") {
        var p1 = rotatePoint(x1, y1, c[0], c[1], "right");
        var p2 = rotatePoint(x2, y2, c[0], c[1], "right");
        var p3 = rotatePoint(x3, y3, c[0], c[1], "right");
        var p4 = rotatePoint(x4, y4, c[0], c[1], "right");
    }

    else if (dir == "left") {
        var p1 = rotatePoint(x1, y1, c[0], c[1], "left");
        var p2 = rotatePoint(x2, y2, c[0], c[1], "left");
        var p3 = rotatePoint(x3, y3, c[0], c[1], "left");
        var p4 = rotatePoint(x4, y4, c[0], c[1], "left");
    }

    rectPoints = [p1[0], p1[1], p2[0], p2[1], p3[0], p3[1], p4[0], p4[1]];

    // draw new rectangle
    drawRectangle(ctx, p1[0], p1[1], p2[0], p2[1], p3[0], p3[1], p4[0], p4[1]);
}

function scaleRectangle(ctx, x1, y1, x2, y2, x3, y3, x4, y4, dir) {
    // erase current rectangle
    clearRectangle(ctx, x1, y1, x2, y2, x3, y3, x4, y4);

    const c = findRectMidpoint(x1, y1, x2, y2, x3, y3, x4, y4);

    // rotate each point based on the midpoint
    if (dir == "up") {
        var p1 = scalePoint(x1, y1, c[0], c[1], "up");
        var p2 = scalePoint(x2, y2, c[0], c[1], "up");
        var p3 = scalePoint(x3, y3, c[0], c[1], "up");
        var p4 = scalePoint(x4, y4, c[0], c[1], "up");
    }

    else if (dir == "down") {
        var p1 = scalePoint(x1, y1, c[0], c[1], "down");
        var p2 = scalePoint(x2, y2, c[0], c[1], "down");
        var p3 = scalePoint(x3, y3, c[0], c[1], "down");
        var p4 = scalePoint(x4, y4, c[0], c[1], "down");
    }

    rectPoints = [p1[0], p1[1], p2[0], p2[1], p3[0], p3[1], p4[0], p4[1]];

    // draw new rectangle
    drawRectangle(ctx, p1[0], p1[1], p2[0], p2[1], p3[0], p3[1], p4[0], p4[1]);
}

function translateRectangle(ctx, x1, y1, x2, y2, x3, y3, x4, y4, endP, startP) {
    // erase current rectangle
    clearRectangle(ctx, x1, y1, x2, y2, x3, y3, x4, y4);

    var diff = [endP[0] - startP[0], endP[1] - startP[1]];

    const p1 = translatePoint(x1, y1, diff);
    const p2 = translatePoint(x2, y2, diff);
    const p3 = translatePoint(x3, y3, diff);
    const p4 = translatePoint(x4, y4, diff);

    rectPoints = [p1[0], p1[1], p2[0], p2[1], p3[0], p3[1], p4[0], p4[1]];

    // draw new rectangle
    drawRectangle(ctx, p1[0], p1[1], p2[0], p2[1], p3[0], p3[1], p4[0], p4[1]);
}

function findRectMidpoint(x1, y1, x2, y2, x3, y3, x4, y4) {
    const tx1 = (x1 + x2 + x4) / 3;
    const ty1 = (y1 + y2 + y4) / 3;

    const tx2 = (x2 + x3 + x4) / 3;
    const ty2 = (y2 + y3 + y4) / 3;

    const cx = (tx1 + tx2) / 2;
    const cy = (ty1 + ty2) / 2;

    return [cx, cy];
}

function drawLine(ctx, x1, y1, x2, y2) {
    ctx.strokeStyle = "#ff8c00"; // orange
    ctx.beginPath();
    ctx.moveTo(x1, y1);
    ctx.lineTo(x2, y2);
    ctx.closePath();
    ctx.stroke();
}

function clearLine(ctx, x1, y1, x2, y2) {
    ctx.strokeStyle = "#ffffff";

    for (var i = 0; i < 3; i++) {
        ctx.beginPath();
        ctx.moveTo(x1, y1);
        ctx.lineTo(x2, y2);
        ctx.closePath();
        ctx.stroke();
    }
}

function rotateLine(ctx, x1, y1, x2, y2, dir) {
    clearLine(ctx, x1, y1, x2, y2);

    const cx = (x1 + x2) / 2;
    const cy = (y1 + y2) / 2;

    if (dir == "right") {
        var p1 = rotatePoint(x1, y1, cx, cy, "right");
        var p2 = rotatePoint(x2, y2, cx, cy, "right");
    }

    else if (dir == "left") {
        var p1 = rotatePoint(x1, y1, cx, cy, "left");
        var p2 = rotatePoint(x2, y2, cx, cy, "left");
    }

    linePoints = [p1[0], p1[1], p2[0], p2[1]];

    drawLine(ctx, p1[0], p1[1], p2[0], p2[1]);
}

function translateLine(ctx, x1, y1, x2, y2, endP, startP) {
    clearLine(ctx, x1, y1, x2, y2);

    var diff = [endP[0] - startP[0], endP[1] - startP[1]];

    const p1 = translatePoint(x1, y1, diff);
    const p2 = translatePoint(x2, y2, diff);

    linePoints = [p1[0], p1[1], p2[0], p2[1]];

    drawLine(ctx, p1[0], p1[1], p2[0], p2[1]);
}

function drawPentagon(ctx, x1, y1, x2, y2, x3, y3, x4, y4, x5, y5) {
    ctx.fillStyle = "#39e6dd"; // cyan
    ctx.beginPath();
    ctx.moveTo(x1, y1);
    ctx.lineTo(x2, y2);
    ctx.lineTo(x3, y3);
    ctx.lineTo(x4, y4);
    ctx.lineTo(x5, y5);
    ctx.closePath();
    ctx.fill();
}

function clearPentagon(ctx, x1, y1, x2, y2, x3, y3, x4, y4, x5, y5) {
    ctx.fillStyle = "#ffffff"; // white
    ctx.strokeStyle = "#ffffff";

    for (var i = 0; i < 3; i++) {
    ctx.beginPath();
        ctx.moveTo(x1, y1);
        ctx.lineTo(x2, y2);
        ctx.lineTo(x3, y3);
        ctx.lineTo(x4, y4);
        ctx.lineTo(x5, y5);
        ctx.closePath();
        ctx.fill();
        ctx.stroke();
    }
}

function rotatePentagon(ctx, x1, y1, x2, y2, x3, y3, x4, y4, x5, y5, dir) {
    // erase current pentagon
    clearPentagon(ctx, x1, y1, x2, y2, x3, y3, x4, y4, x5, y5);

    const c = findPentMidpoint(x1, y1, x2, y2, x3, y3, x4, y4, x5, y5);

    // rotate each point based on the midpoint
    if (dir == "right") {
        var p1 = rotatePoint(x1, y1, c[0], c[1], "right");
        var p2 = rotatePoint(x2, y2, c[0], c[1], "right");
        var p3 = rotatePoint(x3, y3, c[0], c[1], "right");
        var p4 = rotatePoint(x4, y4, c[0], c[1], "right");
        var p5 = rotatePoint(x5, y5, c[0], c[1], "right");
    }

    else if (dir == "left") {
        var p1 = rotatePoint(x1, y1, c[0], c[1], "left");
        var p2 = rotatePoint(x2, y2, c[0], c[1], "left");
        var p3 = rotatePoint(x3, y3, c[0], c[1], "left");
        var p4 = rotatePoint(x4, y4, c[0], c[1], "left");
        var p5 = rotatePoint(x5, y5, c[0], c[1], "left");
    }

    pentPoints = [p1[0], p1[1], p2[0], p2[1], p3[0], p3[1], p4[0], p4[1], p5[0], p5[1]];

    // draw new pentagon
    drawPentagon(ctx, p1[0], p1[1], p2[0], p2[1], p3[0], p3[1], p4[0], p4[1], p5[0], p5[1]);
}

function scalePentagon(ctx, x1, y1, x2, y2, x3, y3, x4, y4, x5, y5, dir) {
    // erase current pentagon
    clearPentagon(ctx, x1, y1, x2, y2, x3, y3, x4, y4, x5, y5);

    const c = findPentMidpoint(x1, y1, x2, y2, x3, y3, x4, y4, x5, y5);

    // rotate each point based on the midpoint
    if (dir == "up") {
        var p1 = scalePoint(x1, y1, c[0], c[1], "up");
        var p2 = scalePoint(x2, y2, c[0], c[1], "up");
        var p3 = scalePoint(x3, y3, c[0], c[1], "up");
        var p4 = scalePoint(x4, y4, c[0], c[1], "up");
        var p5 = scalePoint(x5, y5, c[0], c[1], "up");
    }

    else if (dir == "down") {
        var p1 = scalePoint(x1, y1, c[0], c[1], "down");
        var p2 = scalePoint(x2, y2, c[0], c[1], "down");
        var p3 = scalePoint(x3, y3, c[0], c[1], "down");
        var p4 = scalePoint(x4, y4, c[0], c[1], "down");
        var p5 = scalePoint(x5, y5, c[0], c[1], "down");
    }

    pentPoints = [p1[0], p1[1], p2[0], p2[1], p3[0], p3[1], p4[0], p4[1], p5[0], p5[1]];

    // draw new pentagon
    drawPentagon(ctx, p1[0], p1[1], p2[0], p2[1], p3[0], p3[1], p4[0], p4[1], p5[0], p5[1]);
}

function translatePentagon(ctx, x1, y1, x2, y2, x3, y3, x4, y4, x5, y5, endP, startP) {
    // erase current pentagon
    clearPentagon(ctx, x1, y1, x2, y2, x3, y3, x4, y4, x5, y5);

    var diff = [endP[0] - startP[0], endP[1] - startP[1]];

    const p1 = translatePoint(x1, y1, diff);
    const p2 = translatePoint(x2, y2, diff);
    const p3 = translatePoint(x3, y3, diff);
    const p4 = translatePoint(x4, y4, diff);
    const p5 = translatePoint(x5, y5, diff);

    pentPoints = [p1[0], p1[1], p2[0], p2[1], p3[0], p3[1], p4[0], p4[1], p5[0], p5[1]];

    // draw new pentagon
    drawPentagon(ctx, p1[0], p1[1], p2[0], p2[1], p3[0], p3[1], p4[0], p4[1], p5[0], p5[1]);
}

// this formula is from https://math.stackexchange.com/questions/86073/geometrically-find-the-center-of-a-pentagon-or-hexagon
// it does not find the exact midpoint but it is pretty close and its the only formula I could find.
// since it does not find the exact midpoint, the rotating looks kind of weird
function findPentMidpoint(x1, y1, x2, y2, x3, y3, x4, y4, x5, y5) {
    var x = [x1, x2, x3, x4, x5, x1];
    var y = [y1, y2, y3, y4, y5, y1];

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

    return [x1, cy];
}
