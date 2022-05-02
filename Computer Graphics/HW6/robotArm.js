"use strict";

var canvas, gl, program;

var NumVertices = 36; //(6 faces)(2 triangles/face)(3 vertices/triangle)

var points = [];
var colors = [];

var vertices = [
    vec4( -0.5, -0.5,  0.5, 1.0 ),
    vec4( -0.5,  0.5,  0.5, 1.0 ),
    vec4(  0.5,  0.5,  0.5, 1.0 ),
    vec4(  0.5, -0.5,  0.5, 1.0 ),
    vec4( -0.5, -0.5, -0.5, 1.0 ),
    vec4( -0.5,  0.5, -0.5, 1.0 ),
    vec4(  0.5,  0.5, -0.5, 1.0 ),
    vec4(  0.5, -0.5, -0.5, 1.0 )
];

// RGBA colors
var vertexColors = [
    vec4( 0.0, 0.0, 0.0, 1.0 ),  // black
    vec4( 1.0, 0.0, 0.0, 1.0 ),  // red
    vec4( 1.0, 1.0, 0.0, 1.0 ),  // yellow
    vec4( 0.0, 1.0, 0.0, 1.0 ),  // green
    vec4( 0.0, 0.0, 1.0, 1.0 ),  // blue
    vec4( 1.0, 0.0, 1.0, 1.0 ),  // magenta
    vec4( 1.0, 1.0, 1.0, 1.0 ),  // white
    vec4( 0.0, 1.0, 1.0, 1.0 )   // cyan
];


// Parameters controlling the size of the Robot's arm

var BASE_HEIGHT      = 2.0;
var BASE_WIDTH       = 5.0;
var LOWER_ARM_HEIGHT = 4.0;
var LOWER_ARM_WIDTH  = 1.0;
var UPPER_ARM_HEIGHT = 4.0;
var UPPER_ARM_WIDTH  = 1.0;

var FINGER1_HEIGHT = 2.0;
var FINGER1_WIDTH  = 0.5;
var FINGER2_HEIGHT = 2.0;
var FINGER2_WIDTH  = 0.5;
var FINGER3_HEIGHT = 2.0;
var FINGER3_WIDTH  = 0.5;


// Shader transformation matrices

var modelViewMatrix, projectionMatrix;

// Array of rotation angles (in degrees) for each rotation axis

var Base = 0;
var LowerArm = 1;
var UpperArm = 2;
var Finger1 = 3;
var Finger2 = 4;
var Finger3 = 5;


var theta= [ 0, 0, 0, 45, 90, 135 ];

var angle = 0;

var modelViewMatrixLoc;

var vBuffer, cBuffer;

var bodyRotationAxis = "y";
var lowerArmRotationAxis = "z";
var upperArmRotationAxis = "z";
var finger1RotationAxis = "z";
var finger2RotationAxis = "z";
var finger3RotationAxis = "z";

//----------------------------------------------------------------------------

function quad(  a,  b,  c,  d ) {
    colors.push(vertexColors[a]);
    points.push(vertices[a]);
    colors.push(vertexColors[a]);
    points.push(vertices[b]);
    colors.push(vertexColors[a]);
    points.push(vertices[c]);
    colors.push(vertexColors[a]);
    points.push(vertices[a]);
    colors.push(vertexColors[a]);
    points.push(vertices[c]);
    colors.push(vertexColors[a]);
    points.push(vertices[d]);
}


function colorCube() {
    quad( 1, 0, 3, 2 );
    quad( 2, 3, 7, 6 );
    quad( 3, 0, 4, 7 );
    quad( 6, 5, 1, 2 );
    quad( 4, 5, 6, 7 );
    quad( 5, 4, 0, 1 );
}

//____________________________________________

// Remmove when scale in MV.js supports scale matrices

function scale4(a, b, c) {
   var result = mat4();
   result[0][0] = a;
   result[1][1] = b;
   result[2][2] = c;
   return result;
}


//--------------------------------------------------


window.onload = function init() {

    canvas = document.getElementById( "gl-canvas" );

    gl = WebGLUtils.setupWebGL( canvas );
    if ( !gl ) { alert( "WebGL isn't available" ); }

    gl.viewport( 0, 0, canvas.width, canvas.height );

    gl.clearColor( 1.0, 1.0, 1.0, 1.0 );
    gl.enable( gl.DEPTH_TEST );

    //
    //  Load shaders and initialize attribute buffers
    //
    program = initShaders( gl, "vertex-shader", "fragment-shader" );

    gl.useProgram( program );

    colorCube();

    // Load shaders and use the resulting shader program

    program = initShaders( gl, "vertex-shader", "fragment-shader" );
    gl.useProgram( program );

    // Create and initialize  buffer objects

    vBuffer = gl.createBuffer();
    gl.bindBuffer( gl.ARRAY_BUFFER, vBuffer );
    gl.bufferData( gl.ARRAY_BUFFER, flatten(points), gl.STATIC_DRAW );

    var vPosition = gl.getAttribLocation( program, "vPosition" );
    gl.vertexAttribPointer( vPosition, 4, gl.FLOAT, false, 0, 0 );
    gl.enableVertexAttribArray( vPosition );

    cBuffer = gl.createBuffer();
    gl.bindBuffer( gl.ARRAY_BUFFER, cBuffer );
    gl.bufferData( gl.ARRAY_BUFFER, flatten(colors), gl.STATIC_DRAW );

    var vColor = gl.getAttribLocation( program, "vColor" );
    gl.vertexAttribPointer( vColor, 4, gl.FLOAT, false, 0, 0 );
    gl.enableVertexAttribArray( vColor );

    document.getElementById("slider1").onchange = function(event) {
        theta[0] = event.target.value;
    };
    document.getElementById("slider2").onchange = function(event) {
        theta[1] = event.target.value;
    };
    document.getElementById("slider3").onchange = function(event) {
        theta[2] =  event.target.value;
    };
    document.getElementById("slider4").onchange = function(event) {
        theta[3] =  event.target.value;
    };
    document.getElementById("slider5").onchange = function(event) {
        theta[4] =  event.target.value;
    };
    document.getElementById("slider6").onchange = function(event) {
        theta[5] =  event.target.value;
    };

    modelViewMatrixLoc = gl.getUniformLocation(program, "modelViewMatrix");

    projectionMatrix = ortho(-10, 10, -10, 10, -10, 10);
    gl.uniformMatrix4fv( gl.getUniformLocation(program, "projectionMatrix"),  false, flatten(projectionMatrix) );

    render();
}

//--------------------------------------------------

function updateBodyAxis() {
    var axis = document.getElementById("slider1Rotation").value;

    if (axis == "x") {
        bodyRotationAxis = "x";
    }
    else if (axis == "y") {
        bodyRotationAxis = "y";
    }
    else if (axis == "z") {
        bodyRotationAxis = "z";
    }
}

function updateLowerArmAxis() {
    var axis = document.getElementById("slider2Rotation").value;

    if (axis == "x") {
        lowerArmRotationAxis = "x";
    }
    else if (axis == "y") {
        lowerArmRotationAxis = "y";
    }
    else if (axis == "z") {
        lowerArmRotationAxis = "z";
    }
}

function updateUpperArmAxis() {
    var axis = document.getElementById("slider3Rotation").value;

    if (axis == "x") {
        upperArmRotationAxis = "x";
    }
    else if (axis == "y") {
        upperArmRotationAxis = "y";
    }
    else if (axis == "z") {
        upperArmRotationAxis = "z";
    }
}

function updateFinger1Axis() {
    var axis = document.getElementById("slider4Rotation").value;

    if (axis == "x") {
        finger1RotationAxis = "x";
    }
    else if (axis == "y") {
        finger1RotationAxis = "y";
    }
    else if (axis == "z") {
        finger1RotationAxis = "z";
    }
}

function updateFinger2Axis() {
    var axis = document.getElementById("slider5Rotation").value;

    if (axis == "x") {
        finger2RotationAxis = "x";
    }
    else if (axis == "y") {
        finger2RotationAxis = "y";
    }
    else if (axis == "z") {
        finger2RotationAxis = "z";
    }
}

function updateFinger3Axis() {
    var axis = document.getElementById("slider6Rotation").value;

    if (axis == "x") {
        finger3RotationAxis = "x";
    }
    else if (axis == "y") {
        finger3RotationAxis = "y";
    }
    else if (axis == "z") {
        finger3RotationAxis = "z";
    }
}

//----------------------------------------------------------------------------


function base() {
    var s = scale4(BASE_WIDTH, BASE_HEIGHT, BASE_WIDTH);
    var instanceMatrix = mult( translate( 0.0, 0.5 * BASE_HEIGHT, 0.0 ), s);
    var t = mult(modelViewMatrix, instanceMatrix);
    gl.uniformMatrix4fv(modelViewMatrixLoc,  false, flatten(t) );
    gl.drawArrays( gl.TRIANGLES, 0, NumVertices );
}

//----------------------------------------------------------------------------


function upperArm() {
    var s = scale4(UPPER_ARM_WIDTH, UPPER_ARM_HEIGHT, UPPER_ARM_WIDTH);
    var instanceMatrix = mult(translate( 0.0, 0.5 * UPPER_ARM_HEIGHT, 0.0 ),s);
    var t = mult(modelViewMatrix, instanceMatrix);
    gl.uniformMatrix4fv( modelViewMatrixLoc,  false, flatten(t) );
    gl.drawArrays( gl.TRIANGLES, 0, NumVertices );
}

//----------------------------------------------------------------------------


function lowerArm()
{
    var s = scale4(LOWER_ARM_WIDTH, LOWER_ARM_HEIGHT, LOWER_ARM_WIDTH);
    var instanceMatrix = mult( translate( 0.0, 0.5 * LOWER_ARM_HEIGHT, 0.0 ), s);
    var t = mult(modelViewMatrix, instanceMatrix);
    gl.uniformMatrix4fv( modelViewMatrixLoc,  false, flatten(t) );
    gl.drawArrays( gl.TRIANGLES, 0, NumVertices );
}

//----------------------------------------------------------------------------

function finger1() {
    var s = scale4(FINGER1_WIDTH, FINGER1_HEIGHT, FINGER1_WIDTH);
    var instanceMatrix = mult( translate( 0.0, 0.5 * FINGER1_HEIGHT, 0.0 ), s);
    var t = mult(modelViewMatrix, instanceMatrix);
    gl.uniformMatrix4fv( modelViewMatrixLoc,  false, flatten(t) );
    gl.drawArrays( gl.TRIANGLES, 0, NumVertices );
}

function finger2() {
    var s = scale4(FINGER2_WIDTH, FINGER2_HEIGHT, FINGER2_WIDTH);
    var instanceMatrix = mult( translate( 0.0, 0.5 * FINGER2_HEIGHT, 0.0 ), s);
    var t = mult(modelViewMatrix, instanceMatrix);
    gl.uniformMatrix4fv( modelViewMatrixLoc,  false, flatten(t) );
    gl.drawArrays( gl.TRIANGLES, 0, NumVertices );
}

function finger3() {
    var s = scale4(FINGER3_WIDTH, FINGER3_HEIGHT, FINGER3_WIDTH);
    var instanceMatrix = mult( translate( 0.0, 0.5 * FINGER3_HEIGHT, 0.0 ), s);
    var t = mult(modelViewMatrix, instanceMatrix);
    gl.uniformMatrix4fv( modelViewMatrixLoc,  false, flatten(t) );
    gl.drawArrays( gl.TRIANGLES, 0, NumVertices );
}

//----------------------------------------------------------------------------


var render = function() {

    gl.clear( gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT );

    if (bodyRotationAxis == "x") {
        modelViewMatrix = rotate(theta[Base], 1, 0, 0 );
    }
    else if (bodyRotationAxis == "y") {
        modelViewMatrix = rotate(theta[Base], 0, 1, 0 );
    }
    else if (bodyRotationAxis == "z") {
        modelViewMatrix = rotate(theta[Base], 0, 0, 1 );
    }
    base();

    modelViewMatrix = mult(modelViewMatrix, translate(0.0, BASE_HEIGHT, 0.0));
    if (lowerArmRotationAxis == "x") {
        modelViewMatrix = mult(modelViewMatrix, rotate(theta[LowerArm], 1, 0, 0 ));
    }
    else if (lowerArmRotationAxis == "y") {
        modelViewMatrix = mult(modelViewMatrix, rotate(theta[LowerArm], 0, 1, 0 ));
    }
    else if (lowerArmRotationAxis == "z") {
        modelViewMatrix = mult(modelViewMatrix, rotate(theta[LowerArm], 0, 0, 1 ));
    }
    lowerArm();

    modelViewMatrix  = mult(modelViewMatrix, translate(0.0, LOWER_ARM_HEIGHT, 0.0));
    if (upperArmRotationAxis == "x") {
        modelViewMatrix = mult(modelViewMatrix, rotate(theta[UpperArm], 1, 0, 0 ));
    }
    else if (upperArmRotationAxis == "y") {
        modelViewMatrix = mult(modelViewMatrix, rotate(theta[UpperArm], 0, 1, 0 ));
    }
    else if (upperArmRotationAxis == "z") {
        modelViewMatrix = mult(modelViewMatrix, rotate(theta[UpperArm], 0, 0, 1 ));
    }
    upperArm();

    modelViewMatrix  = mult(modelViewMatrix, translate(0.0, FINGER1_HEIGHT, 0.0));
    if (finger1RotationAxis == "x") {
        modelViewMatrix = mult(modelViewMatrix, rotate(theta[Finger1], 1, 0, 0 ));
    }
    else if (finger1RotationAxis == "y") {
        modelViewMatrix = mult(modelViewMatrix, rotate(theta[Finger1], 0, 1, 0 ));
    }
    else if (finger1RotationAxis == "z") {
        modelViewMatrix = mult(modelViewMatrix, rotate(theta[Finger1], 0, 0, 1 ));
    }
    finger1();

    // modelViewMatrix  = mult(modelViewMatrix, translate(0.0, FINGER2_HEIGHT, 0.0));
    if (finger2RotationAxis == "x") {
        modelViewMatrix = mult(modelViewMatrix, rotate(theta[Finger2], 1, 0, 0 ));
    }
    else if (finger2RotationAxis == "y") {
        modelViewMatrix = mult(modelViewMatrix, rotate(theta[Finger2], 0, 1, 0 ));
    }
    else if (finger2RotationAxis == "z") {
        modelViewMatrix = mult(modelViewMatrix, rotate(theta[Finger2], 0, 0, 1 ));
    }
    finger2();

    // modelViewMatrix  = mult(modelViewMatrix, translate(0.0, FINGER3_HEIGHT, 0.0));
    if (finger3RotationAxis == "x") {
        modelViewMatrix = mult(modelViewMatrix, rotate(theta[Finger3], 1, 0, 0 ));
    }
    else if (finger3RotationAxis == "y") {
        modelViewMatrix = mult(modelViewMatrix, rotate(theta[Finger3], 0, 1, 0 ));
    }
    else if (finger3RotationAxis == "z") {
        modelViewMatrix = mult(modelViewMatrix, rotate(theta[Finger3], 0, 0, 1 ));
    }
    finger3();

    requestAnimFrame(render);
}
