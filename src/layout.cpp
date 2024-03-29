#include "../include/layout.h"

void Layout::init(){
    windowWidth = WINDOW_WIDTH;
    windowHeight = WINDOW_HEIGHT;
	// windowWidth = WINDOW_WIDTH;
	// windowHeight = WINDOW_HEIGHT;
	headerFontSize = 20;

	// Headers text positions
    headersPos[0] = {10, H1(WINDOW_HEIGHT) + 10};                    // Prior
    headersPos[1] = {10, H2(WINDOW_HEIGHT) + 10};                    // Channel
    headersPos[2] = {V1(WINDOW_WIDTH) - 180, H2(WINDOW_HEIGHT) + 10}; // Channel outputs
    headersPos[3] = {10, H3(WINDOW_HEIGHT) + 10};                    // Gain Function
    headersPos[4] = {V1(WINDOW_WIDTH) + 10, H1(WINDOW_HEIGHT) + 10};  // Inner distributions

	// Main Triangle Features
    trianglePos[0] = {TRIANGLEV2(WINDOW_WIDTH, WINDOW_HEIGHT), TRIANGLEH2(WINDOW_WIDTH, WINDOW_HEIGHT)}; // X1
    trianglePos[1] = {TRIANGLEV1(WINDOW_WIDTH, WINDOW_HEIGHT), TRIANGLEH3(WINDOW_WIDTH, WINDOW_HEIGHT)}; // X2
    trianglePos[2] = {TRIANGLEV3(WINDOW_WIDTH, WINDOW_HEIGHT), TRIANGLEH3(WINDOW_WIDTH, WINDOW_HEIGHT)}; // X3    
    triangleTextPos[0] = {TRIANGLEV2(WINDOW_WIDTH, WINDOW_HEIGHT) - 0.01f * WINDOW_WIDTH, TRIANGLEH2(WINDOW_WIDTH, WINDOW_HEIGHT) - 0.03f * WINDOW_HEIGHT}; // X1
    triangleTextPos[1] = {TRIANGLEV1(WINDOW_WIDTH, WINDOW_HEIGHT) - 0.03f * WINDOW_WIDTH, TRIANGLEH3(WINDOW_WIDTH, WINDOW_HEIGHT) - 0.01f * WINDOW_HEIGHT}; // X2
    triangleTextPos[2] = {TRIANGLEV3(WINDOW_WIDTH, WINDOW_HEIGHT) + 0.01f * WINDOW_WIDTH, TRIANGLEH3(WINDOW_WIDTH, WINDOW_HEIGHT) - 0.01f * WINDOW_HEIGHT}; // X3

    // Interface rectangles
    staticRectangles[PRIOR]           = (Rectangle){				  0.0f, (float)H1(WINDOW_HEIGHT), 	  (float)V1(WINDOW_WIDTH)+1, (float)(H2(WINDOW_HEIGHT) - H1(WINDOW_HEIGHT))+1};
    staticRectangles[CHANNEL]         = (Rectangle){				  0.0f, (float)H2(WINDOW_HEIGHT), 	  (float)V1(WINDOW_WIDTH)+1, (float)(H3(WINDOW_HEIGHT) - H2(WINDOW_HEIGHT))+1};
    staticRectangles[CHANNEL_SPINNER] = (Rectangle){V1(WINDOW_WIDTH) - 90,   H2(WINDOW_HEIGHT) + 10, 						 80.0f, 									     20.0f};
    staticRectangles[GAIN]            = (Rectangle){				  0.0f, (float)H3(WINDOW_HEIGHT), 	  (float)V1(WINDOW_WIDTH)+1, 	(float)(WINDOW_HEIGHT - H3(WINDOW_HEIGHT))+1};
    staticRectangles[INNERS]          = (Rectangle){	   V1(WINDOW_WIDTH), 	   H1(WINDOW_HEIGHT), WINDOW_WIDTH - V1(WINDOW_WIDTH), 							 TH1(WINDOW_HEIGHT)};
    staticRectangles[DRAW_CHECK_BOX]  = (Rectangle){V1(WINDOW_WIDTH)/2.0f - 30, H2(WINDOW_HEIGHT)+ 120 + 2*(BOX_HEIGHT+2*BOX_VER_GAP), 15.0f, 15.0f};
    // staticrectangles[GAIN_SPINNER]    = (Rectangle){				  0.0f, (float)H3(windowHeight), 	  (float)V1(windowWidth)+1, 	(float)(windowHeight - H3(windowHeight))+1};
}

void Layout::update(int windowWidth, int windowHeight){
	this->windowWidth = windowWidth;
	this->windowHeight = windowHeight;

	// Headers text positions
    headersPos[0] = {10, H1(windowHeight) + 10};                    // Prior
    headersPos[1] = {10, H2(windowHeight) + 10};                    // Channel
    headersPos[2] = {V1(windowWidth) - 180, H2(windowHeight) + 10}; // Channel outputs
    headersPos[3] = {10, H3(windowHeight) + 10};                    // Gain Function
    headersPos[4] = {V1(windowWidth) + 10, H1(windowHeight) + 10};  // Inner distributions

    // Main Triangle Features
    trianglePos[0] = {TRIANGLEV2(windowWidth, windowHeight), TRIANGLEH2(windowWidth, windowHeight)}; // X1
    trianglePos[1] = {TRIANGLEV1(windowWidth, windowHeight), TRIANGLEH3(windowWidth, windowHeight)}; // X2
    trianglePos[2] = {TRIANGLEV3(windowWidth, windowHeight), TRIANGLEH3(windowWidth, windowHeight)}; // X3
    triangleTextPos[0] = {TRIANGLEV2(windowWidth, windowHeight) - 0.01f * windowWidth, TRIANGLEH2(windowWidth, windowHeight) - 0.03f * windowHeight}; // X1
    triangleTextPos[1] = {TRIANGLEV1(windowWidth, windowHeight) - 0.03f * windowWidth, TRIANGLEH3(windowWidth, windowHeight) - 0.01f * windowHeight}; // X2
    triangleTextPos[2] = {TRIANGLEV3(windowWidth, windowHeight) + 0.01f * windowWidth, TRIANGLEH3(windowWidth, windowHeight) - 0.01f * windowHeight}; // X3

    // Interface rectangles
    staticRectangles[PRIOR]           = (Rectangle){				  0.0f, (float)H1(windowHeight), 	  (float)V1(windowWidth)+1, (float)(H2(windowHeight) - H1(windowHeight))+1};
    staticRectangles[CHANNEL]         = (Rectangle){				  0.0f, (float)H2(windowHeight), 	  (float)V1(windowWidth)+1, (float)(H3(windowHeight) - H2(windowHeight))+1};
    staticRectangles[CHANNEL_SPINNER] = (Rectangle){V1(windowWidth) - 90,   H2(windowHeight) + 10, 						 80.0f, 									     20.0f};
    staticRectangles[GAIN]            = (Rectangle){				  0.0f, (float)H3(windowHeight), 	  (float)V1(windowWidth)+1, 	(float)(windowHeight - H3(windowHeight))+1};
    staticRectangles[INNERS]          = (Rectangle){	   V1(windowWidth), 	   H1(windowHeight), windowWidth - V1(windowWidth), 							 TH1(windowHeight)};
    staticRectangles[DRAW_CHECK_BOX]  = (Rectangle){V1(windowWidth)/2.0f - 30, H2(windowHeight)+ 120 + 2*(BOX_HEIGHT+2*BOX_VER_GAP), 15.0f, 15.0f};
}

void Layout::draw(Colors colors){
	// Rectangles
    DrawRectangleRec(staticRectangles[PRIOR],   colors.recColor); DrawRectangleLinesEx(staticRectangles[PRIOR],   1, colors.recBorderColor);
    DrawRectangleRec(staticRectangles[CHANNEL], colors.recColor); DrawRectangleLinesEx(staticRectangles[CHANNEL], 1, colors.recBorderColor);
    DrawRectangleRec(staticRectangles[GAIN],    colors.recColor); DrawRectangleLinesEx(staticRectangles[GAIN],    1, colors.recBorderColor);
    DrawRectangleRec(staticRectangles[INNERS],  colors.recColor); DrawRectangleLinesEx(staticRectangles[INNERS],  1, colors.recBorderColor);

	// Text
    DrawText("Prior distribution" , headersPos[0].x, headersPos[0].y, headerFontSize, BLACK);
    DrawText("Channel"            , headersPos[1].x, headersPos[1].y, headerFontSize, BLACK);
    DrawText("Outputs: "          , headersPos[2].x, headersPos[2].y, headerFontSize, BLACK);
    DrawText("Gain Function"      , headersPos[3].x, headersPos[3].y, headerFontSize, BLACK);
    DrawText("Inner distributions", headersPos[4].x, headersPos[4].y, headerFontSize, BLACK);

	// Main Triangle
    DrawTriangleLines(trianglePos[0], trianglePos[1], trianglePos[2], BLACK); 
    DrawText("X1", triangleTextPos[0].x, triangleTextPos[0].y, headerFontSize, BLACK);
    DrawText("X2", triangleTextPos[1].x, triangleTextPos[1].y, headerFontSize, BLACK);
    DrawText("X3", triangleTextPos[2].x, triangleTextPos[2].y, headerFontSize, BLACK);

    // Channel
    // GuiSpinner(staticRectangles[CHANNEL_SPINNER], &numOutputs, 1, MAX_OUTPUTS, true);
}