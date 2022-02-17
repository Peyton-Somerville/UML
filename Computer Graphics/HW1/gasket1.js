"use strict";

var gl;
var points;

var NumPoints = 5000;

// shaders taken from HTML and made into a string
var vertexShaderStr = 
    "attribute vec4 vPosition;" +
    "void main() { " + 
	"    gl_PointSize = 1.0;" + 
    "    gl_Position = vPosition;" + 
    "}";

var fragmentShaderStr = 
    "precision mediump float;" +
    "void main() {" +
    "    gl_FragColor = vec4( 1.0, 0.0, 0.0, 1.0 );" +
    "}";

// index for animation loop
var i = 0;

// initial canvas properties
var w = 512;
var h = 512;
var x = 0;
var y = 0;

// starts the animation loop with initial interval of 500ms(0.5 sec) pauses
var speed = 500;
var interval = setInterval(renderLoop, speed);

var colors = [
    vec4(1.0, 0.0, 0.0, 1.0),  // red
    vec4(1.0, 1.0, 0.0, 1.0),  // yellow
    vec4(1.0, 0.0, 1.0, 1.0),  // light purple
    vec4(0.0, 1.0, 0.0, 1.0),  // light green
    vec4(0.0, 1.0, 1.0, 1.0),  // light blue
    vec4(0.8, 0.5, 0.0, 1.0),  // orange
    vec4(0.6, 0.0, 1.0, 1.0),  // dark purple
    vec4(0.0, 0.3, 0.2, 1.0),  // dark green
    vec4(0.0, 0.0, 1.0, 1.0),  // dark blue
    vec4(1.0, 0.5, 1.0, 1.0)]; // pink

window.onload = function init()
{
    var canvas = document.getElementById( "gl-canvas" );

    gl = WebGLUtils.setupWebGL( canvas );
    if ( !gl ) { alert( "WebGL isn't available" ); }

    // generate points
    initGasket(NumPoints);

    //  Configure WebGL
    gl.viewport( 0, 0, canvas.width, canvas.height );
    gl.clearColor( 1.0, 1.0, 1.0, 1.0 );

    //  Load shaders and initialize attribute buffers

    // custom shader initialization function
    var program = initMyShaders(gl, vertexShaderStr, fragmentShaderStr);
    gl.useProgram(program);

    initBuffer(program);
};

// gets called every $(speed)ms by the setInterval function
function renderLoop() {
    // display the gasket
    render(i, w, h, NumPoints, x, y);

    // update properties of gasket
    i++;
    w -= 40;
    h -= 40;
    x += 20;
    y += 20;
    NumPoints -= 450;

    // after 10 iterations, reset values
    if (i >= 10) {
        i = 0;
        w = 512;
        h = 512;
        x = 0;
        y = 0;
        NumPoints = 5000;
    }
}

// displays our gasket
function render(index, width, height, numPoints, xPos, yPos) {
    // generate points
    initGasket(numPoints);

    gl.clear( gl.COLOR_BUFFER_BIT );
    
    // set position and size
    gl.viewport(xPos, yPos, width, height);

    // edited shader code so gl_FragColor uses a uniform vec4 color variable
    fragmentShaderStr = 
        "precision mediump float;" +
        "uniform vec4 color;" +
        "void main() {" +
        "    gl_FragColor = color;" +
        "}";

    var program = initMyShaders(gl, vertexShaderStr, fragmentShaderStr);
    gl.useProgram(program);

    // get location of uniform vec4 color variable in shader code
    var colorLocation = gl.getUniformLocation(program, "color");

    // set the value of the color variable
    gl.uniform4fv(colorLocation, colors[index])

    initBuffer(program);
    gl.drawArrays( gl.POINTS, 0, points.length );
}

// generates points for the gasket
function initGasket(numPoints) {
    //
    //  Initialize our data for the Sierpinski Gasket
    //

    // First, initialize the corners of our gasket with three points.

    var vertices = [
        vec2( -1, -1 ),
        vec2(  0,  1 ),
        vec2(  1, -1 )
    ];

    // Specify a starting point p for our iterations
    // p must lie inside any set of three vertices

    var u = add( vertices[0], vertices[1] );
    var v = add( vertices[0], vertices[2] );
    var p = scale( 0.25, add( u, v ) );

    // And, add our initial point into our array of points

    points = [ p ];

    // Compute new points
    // Each new point is located midway between
    // last point and a randomly chosen vertex

    for ( var i = 0; points.length < numPoints; ++i ) {
        var j = Math.floor(Math.random() * 3);
        p = add( points[i], vertices[j] );
        p = scale( 0.5, p );
        points.push( p );
    }
}

// creates and compiles shaders
function initMyShaders(gl, vertShaderStr, fragShaderStr) {
    var prog = gl.createProgram();

    var vertexShader = gl.createShader(gl.VERTEX_SHADER);
    gl.shaderSource(vertexShader, vertShaderStr);
    gl.compileShader(vertexShader);
    gl.attachShader(prog, vertexShader);

    var fragmentShader = gl.createShader(gl.FRAGMENT_SHADER);
    gl.shaderSource(fragmentShader, fragShaderStr);
    gl.compileShader(fragmentShader);
    gl.attachShader(prog, fragmentShader);

    gl.linkProgram(prog);

    return prog;
}

// creates and initializes buffer
function initBuffer(prog) {
    // Load the data into the GPU
    var bufferId = gl.createBuffer();
    gl.bindBuffer( gl.ARRAY_BUFFER, bufferId );
    gl.bufferData( gl.ARRAY_BUFFER, flatten(points), gl.STATIC_DRAW );

    // Associate out shader variables with our data buffer
    var vPosition = gl.getAttribLocation( prog, "vPosition" );
    gl.vertexAttribPointer( vPosition, 2, gl.FLOAT, false, 0, 0 );
    gl.enableVertexAttribArray( vPosition );
}

// gets called when the "Stop Animation" button is clicked
function stop() {
    // ends our interval
    clearInterval(interval);

    // hide other buttons to prevent the functionality from being messed up
    document.getElementById("stopBtn").style.visibility = "hidden";
    document.getElementById("speedIncrease").style.visibility = "hidden";
    document.getElementById("speedDecrease").style.visibility = "hidden";

    // make the resume button appear
    document.getElementById("resumeBtn").style.visibility = "visible";
}

// gets called when the "Resume Animation" button is clicked
function resume() {
    // hide resume button and bring back the others
    document.getElementById("resumeBtn").style.visibility = "hidden";
    document.getElementById("stopBtn").style.visibility = "visible";
    document.getElementById("speedIncrease").style.visibility = "visible";
    document.getElementById("speedDecrease").style.visibility = "visible";

    // continues our interval
    interval = setInterval(renderLoop, speed);
}

// gets called when the "Increase Animation Speed" button is clicked
function increaseSpeed() {
    // stop interval
    clearInterval(interval);

    // more speed means lower time interval
    if (speed > 100) {
        speed -= 100;
    }

    //continue with new speed
    interval = setInterval(renderLoop, speed);
}

// gets called when the "Decrease Animation Speed" button is clicked
function decreaseSpeed() {
    // stop interval
    clearInterval(interval);

    // less speed means higher time interval
    if (speed < 5000) {
        speed += 100;
    }

    // continue with new speed
    interval = setInterval(renderLoop, speed);
}