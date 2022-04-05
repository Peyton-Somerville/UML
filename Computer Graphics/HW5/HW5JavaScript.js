var clickFlag = false;
var clickCount = 0;
var curveFlag = false;

var point = [0, 0];
var prev3Points = [];

const n = 200;

window.onload = function init() {
    var canvas = document.getElementById( "canvas" );
    canvas.addEventListener("click", mouseClick);
}

function clearCanvas() {
    var canvas = document.getElementById( "canvas" );
    var ctx = canvas.getContext("2d");

    ctx.clearRect(0, 0, canvas.width, canvas.height);

    clickFlag = false;
}

function updateInstructions() {
    var alg = document.getElementById("drawingAlg").value;
    var str = "";

    switch (alg) {
        case "ddaLine":
            str += "Click once in the canvas to set the starting point, (x0, y0). Click again to set the ending point, (x1, y1). When both points are set, a line between them will be drawn automatically.";
            break;
        
        case "midLine":
            str += "Click once in the canvas to set the starting point, (x0, y0). Click again to set the ending point, (x1, y1). When both points are set, a line between them will be drawn automatically.";
            break;

        case "midCircle":
            str += "Click once in the canvas to set the origin of the circle. Click again to form a line segment whose length will serve as the radius. When the radius is known, the circle will be drawn.";
            break;

        case "midEllipse":
            str += "Click once in the canvas to set the origin of the ellipse. Click again to form a line segment whose dx and dy will serve as a and b for the ellipse. When a and b are known, the ellipse will be drawn.";
            break;
        
        case "bezierCurve":
            str += "Click on the canvas 4 times to set the 4 points, (x1, y1), (x2, y2), (x3, y3), (x4, y4). Once all 4 points have been set, the curve will be drawn.";
            resetClicks();
            break;
            
        case "hermiteCurve":
            str += "Click on the canvas 4 times to set the 4 points, (x1, y1), (x2, y2), (x3, y3), (x4, y4). Once all 4 points have been set, the curve will be drawn.";
            resetClicks();
            break;

        case "splineCurve":
            str += "Click on the canvas 4 times to set the 4 points, (x1, y1), (x2, y2), (x3, y3), (x4, y4). Once all 4 points have been set, the curve will be drawn.";
            resetClicks();
            break;
        default:
            console.log("ERROR: something went wrong which choosing a drawing algorthm.")
            break;
    }

    document.getElementById("instructions").innerHTML = str;
}

function resetClicks() {
    clickCount = 0;
    prev3Points = [];
}

function mouseClick(event) {
    var canvas = document.getElementById( "canvas" );
    var ctx = canvas.getContext("2d");
    var compare = document.getElementById("primCompare").value;
    var alg = document.getElementById("drawingAlg").value;

    const x = event.clientX;
    const y = event.clientY;

    if (prev3Points.length > 6) {
        prev3Points = [];
    }

    if (clickCount == 3) {
        clickCount = 0;
        curveFlag = true;
    }
    else {
        clickCount++;
        curveFlag = false;
        prev3Points.push(x);
        prev3Points.push(y);
    }

    // console.log(prev3Points);
    // console.log("curveFlag = " + curveFlag);

    if (clickFlag == false) {
        // console.log("CLICKED at x:" + x + " y:" + y);
        point = [x, y];
        clickFlag = true;
    }

    else if (clickFlag == true) {
        // console.log("CLICKED at x:" + x + " y:" + y);

        switch (alg) {
            case "ddaLine":
                ddaLine(point[0], point[1], x, y, ctx);

                if (compare == "yes") {
                    drawLine(point[0], point[1], x, y, ctx);
                }
                break;
            
            case "midLine":
                midpointLine(point[0], point[1], x, y, ctx);

                if (compare == "yes") {
                    drawLine(point[0], point[1], x, y, ctx);
                }
                break;

            case "midCircle":
                var radius = findRadius(point[0], point[1], x, y);

                midpointCircle(point[0], point[1], radius, ctx);

                if (compare == "yes") {
                    drawCircle(point[0], point[1], radius, ctx);
                }
                break;

            case "midEllipse":
                var dx = Math.abs(x - point[0]);
                var dy = Math.abs(y - point[1]);

                midpointEllipse(point[0], point[1], dx, dy, ctx);

                if (compare == "yes") {
                    drawEllipse(point[0], point[1], dx, dy, ctx);
                }
                break;
            
            case "bezierCurve":
                if (curveFlag == true) {
                    // console.log("called with", prev3Points[0], prev3Points[1], prev3Points[2], prev3Points[3], prev3Points[4], prev3Points[5]);
                    bezier(prev3Points[0], prev3Points[1], prev3Points[2], prev3Points[3], prev3Points[4], prev3Points[5], x, y, ctx);

                    if (compare == "yes") {
                        drawCruve(prev3Points[0], prev3Points[1], prev3Points[2], prev3Points[3], prev3Points[4], prev3Points[5], x, y, ctx);
                    }

                    prev3Points = [];
                }
                break;
                
            case "hermiteCurve":
                if (curveFlag == true) {
                    // console.log("called with", prev3Points[0], prev3Points[1], prev3Points[2], prev3Points[3], prev3Points[4], prev3Points[5]);
                    hermite(prev3Points[0], prev3Points[1], prev3Points[2], prev3Points[3], prev3Points[4], prev3Points[5], x, y, ctx);

                    if (compare == "yes") {
                        drawCruve(prev3Points[0], prev3Points[1], prev3Points[2], prev3Points[3], prev3Points[4], prev3Points[5], x, y, ctx);
                    }

                    prev3Points = [];
                }
                break;

            case "splineCurve":
                if (curveFlag == true) {
                    // console.log("called with", prev3Points[0], prev3Points[1], prev3Points[2], prev3Points[3], prev3Points[4], prev3Points[5]);
                    spline(prev3Points[0], prev3Points[1], prev3Points[2], prev3Points[3], prev3Points[4], prev3Points[5], x, y, ctx);

                    if (compare == "yes") {
                        drawCruve(prev3Points[0], prev3Points[1], prev3Points[2], prev3Points[3], prev3Points[4], prev3Points[5], x, y, ctx);
                    }

                    prev3Points = [];
                }
                break;
            default:
                console.log("ERROR: something went wrong which choosing a drawing algorthm.")
                break;
        }

        clickFlag = false;
    }
}

function ddaLine(x0, y0, x1, y1, ctx) {
    if (x0 > x1) {
        var temp = x0;
        x0 = x1;
        x1 = temp;

        temp = y0;
        y0 = y1;
        y1 = temp;
    }

    var dy = y1 - y0;
    var dx = x1 - x0;
    var m = dy / dx;
    var y = y0;

    for (var x = x0; x <= x1; x++) {
        // console.log("x=" + x + " y=" + Math.round(y));
        ctx.fillRect(x, Math.round(y), 1, 1);   // draws a 1 pixel point
        y = y + m;
    }
}

function midpointLine(x0, y0, x1, y1, ctx) { 
    if (x0 > x1) {
        var temp = x0;
        x0 = x1;
        x1 = temp;

        temp = y0;
        y0 = y1;
        y1 = temp;
    }

    var dx = x1 - x0;
    var dy = y1 - y0;

    var increment = 0;
    if (dy >= 0) {
        increment = 1;
    }
    else if (dy < 0) {
        increment = -1;
    }

    dy = Math.abs(dy);

    var d = 2 * dy - dx;
    var incrE = 2 * dy;
    var incrNE = 2 * (dy - dx);
    var x = x0;
    var y = y0;
    
    // console.log("x=" + x + " y=" + y);
    ctx.fillRect(x, y, 1, 1);
    while (x < x1) {
        if (d <= 0) {
            d = d + incrE;
            x++;
        }
        else {
            d = d + incrNE;
            x++;
            y += increment;
        }
        // console.log("x=" + x + " y=" + y);
        ctx.fillRect(x, y, 1, 1);
    }
}

function drawLine(x1, y1, x2, y2, ctx) {
    ctx.strokeStyle = "#fc0303"; // red
    ctx.beginPath();
    ctx.moveTo(x1, y1);
    ctx.lineTo(x2, y2);
    ctx.closePath();
    ctx.stroke();
}

function circlePoints(x0, y0, x, y, ctx) {
    ctx.fillRect(x + x0, y + y0, 1, 1);
    ctx.fillRect(y + x0, x + y0, 1, 1);
    ctx.fillRect(y + x0, -x + y0, 1, 1);
    ctx.fillRect(x + x0, -y + y0, 1, 1);
    ctx.fillRect(-x + x0, -y + y0, 1, 1);
    ctx.fillRect(-y + x0, -x + y0, 1, 1);
    ctx.fillRect(-y + x0, x + y0, 1, 1);
    ctx.fillRect(-x + x0, y + y0, 1, 1);
}

function midpointCircle(x0, y0, radius, ctx) { 
    var x = 0;
    var y = radius;
    var d = 5.0 / 4.0 - radius;

    circlePoints(x0, y0, x, y, ctx);
    
    while (y > x) {
        if (d < 0) {
            d = d + 2.0 * x + 3.0;
        }
        else {
            d = d + 2.0 * (x - y) + 5.0;
            y--;
        }
        x++;
        circlePoints(x0, y0, x, y, ctx);
    }
}

function drawCircle(x, y, r, ctx) {
    ctx.strokeStyle = "#fc0303"; // red
    ctx.beginPath();
    ctx.arc(x, y, r, 0, Math.PI * 2);
    ctx.closePath();
    ctx.stroke();
}

function findRadius(x1, y1, x2, y2) {
    x = Math.pow((x2 - x1), 2); 
    y = Math.pow((y2 - y1), 2);

    return Math.round(Math.sqrt(x + y));
}

function ellipsePoints(x0, y0, x, y, ctx) {
    ctx.fillRect(x + x0, y + y0, 1, 1);
    ctx.fillRect(-x + x0, y + y0, 1, 1);
    ctx.fillRect(x + x0, -y + y0, 1, 1);
    ctx.fillRect(-x + x0, -y + y0, 1, 1);
}

function midpointEllipse(x0, y0, a, b, ctx) { 
    var d2;
    var x = 0;
    var y = b;
    var d1 = (b*b) - (a*a*b) + (0.25*a*a);
    
    ellipsePoints(x0, y0, x, y, ctx);
  
    // test gradient if still in region 1
    while (((a*a)*(y-0.5)) > ((b*b)*(x+1))) {
        if (d1 < 0) {
            d1 = d1 + ((b*b)*(2*x+3));
        }
        else {
            d1 = d1 + ((b*b)*(2*x+3)) + ((a*a)*(-2*y+2));
            y--;
        }
        x++;
        ellipsePoints(x0, y0, x, y, ctx);
    }   // Region 1
    
    d2 = ((b*b)*(x+0.5)*(x+0.5))+((a*a)*(y-1)*(y-1))-(a*a*b*b);
    while (y > 0) {
        if (d2 < 0) {
            d2 = d2 + ((b*b)*(2*x+2)) + ((a*a)*(-2*y+3));
            x++;
        }
        else {
            d2 = d2 + ((a*a)*(-2*y+3));
        }
        y--;
        ellipsePoints(x0, y0, x, y, ctx);
    }   // Region 2
}

function drawEllipse(x, y, dx, dy, ctx) {
    ctx.strokeStyle = "#fc0303"; // red
    ctx.beginPath();
    ctx.ellipse(x, y, dx, dy, Math.PI, 0, 2 * Math.PI);
    ctx.stroke();
}

function bezier(x1, y1, x2, y2, x3, y3, x4, y4, ctx) {
    var i;
    var x, y;
    var delta = 1.0/n;
    var t;

    ctx.fillRect(x1, y1, 1, 1);
    // ctx.fillRect(x2, y2, 1, 1);
    // ctx.fillRect(x3, y3, 1, 1);
    ctx.fillRect(x4, y4, 1, 1);

    x = x1;
    y = y1;
    t = 0.0;
    
    for (i = 0; i < n; i++) {
        t += delta;
        var t2 = t * t;
        var t3 = t2 * t;
           
        var q1=(1-t);
        var q2=q1*q1;
        var q3=q2*q1;
        x = q3*x1 + (3*t*q2)*x2 + (3*t2*q1)*x3 + t3*x4;
        y = q3*y1 + (3*t*q2)*y2 + (3*t2*q1)*y3 + t3*y4;
        
        ctx.fillRect(x, y, 1, 1);
    }
}

function hermite(x1, y1, x2, y2, x3, y3, x4, y4, ctx) {
    var i;
    var x, y;
    var delta = 1.0/n;
    var t;

    ctx.fillRect(x1, y1, 1, 1);
    // ctx.fillRect(x2, y2, 1, 1);
    // ctx.fillRect(x3, y3, 1, 1);
    ctx.fillRect(x4, y4, 1, 1);

    x = x1;
    y = y1;
    t = 0.0;
    
    for (i = 0; i < n; i++) {
        t += delta;
        var t2 = t * t;
        var t3 = t2 * t;

        x = ((2*t3)-(3*t2)+1)*x1 + ((-2*t3)+(3*t2))*x4 + (t3-(2*t2)+t)*x2 + (t3-t2)*x3;
        y = ((2*t3)-(3*t2)+1)*y1 + ((-2*t3)+(3*t2))*y4 + (t3-(2*t2)+t)*y2 + (t3-t2)*y3;
        
        ctx.fillRect(x, y, 1, 1);
    }
}

function spline(x1, y1, x2, y2, x3, y3, x4, y4, ctx) {
    var i;
    var x, y;
    var delta = 1.0/n;
    var t;

    /*ctx.fillRect(x1, y1, 1, 1);
    ctx.fillRect(x2, y2, 1, 1);
    ctx.fillRect(x3, y3, 1, 1);
    ctx.fillRect(x4, y4, 1, 1);*/

    x = x1;
    y = y1;
    t = 0.0;
    
    for (i = 0; i < n; i++) {
        t += delta;
        var t2 = t * t;
        var t3 = t2 * t;

        x = (((1-t3)/6)*x1)+(((3*t3-6*t2+4)/6)*x2)+(((-3*t3+3*t2+3*t+1)/6)*x3)+((t3/6)*x4);
        y = (((1-t3)/6)*y1)+(((3*t3-6*t2+4)/6)*y2)+(((-3*t3+3*t2+3*t+1)/6)*y3)+((t3/6)*y4);
        
        ctx.fillRect(x, y, 1, 1);
    }

}

function drawCruve(x1, y1, x2, y2, x3, y3, x4, y4, ctx) {
    ctx.strokeStyle = "#fc0303"; // red
    ctx.beginPath();
    ctx.moveTo(x1, y1);
    ctx.bezierCurveTo(x2, y2, x3, y3, x4, y4);
    ctx.stroke();
}