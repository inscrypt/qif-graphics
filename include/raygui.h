/*******************************************************************************************
*
*   raygui v2.7-dev - A simple and easy-to-use immediate-mode gui library
*
*   DESCRIPTION:
*
*   raygui is a tools-dev-focused immediate-mode-gui library based on raylib but also
*   available as a standalone library, as long as input and drawing functions are provided.
*
*   Controls provided:
*
*   # Container/separators Controls
*       - WindowBox
*       - GroupBox
*       - Line
*       - Panel
*
*   # Basic Controls
*       - Label
*       - Button
*       - LabelButton   --> Label
*       - ImageButton   --> Button
*       - ImageButtonEx --> Button
*       - Toggle
*       - ToggleGroup   --> Toggle
*       - CheckBox
*       - ComboBox
*       - DropdownBox
*       - TextBox
*       - TextBoxMulti
*       - ValueBox      --> TextBox
*       - Spinner       --> Button, ValueBox
*       - Slider
*       - SliderBar     --> Slider
*       - ProgressBar
*       - StatusBar
*       - ScrollBar
*       - ScrollPanel
*       - DummyRec
*       - Grid
*
*   # Advance Controls
*       - ListView
*       - ColorPicker   --> ColorPanel, ColorBarHue
*       - MessageBox    --> Window, Label, Button
*       - TextInputBox  --> Window, Label, TextBox, Button
*
*   It also provides a set of functions for styling the controls based on its properties (size, color).
*
*   CONFIGURATION:
*
*   #define RAYGUI_IMPLEMENTATION
*       Generates the implementation of the library into the included file.
*       If not defined, the library is in header only mode and can be included in other headers
*       or source files without problems. But only ONE file should hold the implementation.
*
*   #define RAYGUI_STATIC (defined by default)
*       The generated implementation will stay private inside implementation file and all
*       internal symbols and functions will only be visible inside that file.
*
*   #define RAYGUI_STANDALONE
*       Avoid raylib.h header inclusion in this file. Data types defined on raylib are defined
*       internally in the library and input management and drawing functions must be provided by
*       the user (check library implementation for further details).
*
*   #define RAYGUI_SUPPORT_RICONS
*       Includes ricons.h header defining a set of 128 icons (binary format) to be used on
*       multiple controls and following raygui styles
*
*   #define RAYGUI_TEXTBOX_EXTENDED
*       Enables advance GuiTextBox()implementation with text selection and copy/cut/paste support
*
*   VERSIONS HISTORY:
*       2.6 (09-Sep-2019) ADDED: GuiTextInputBox()
*                         REDESIGNED: GuiListView*(), GuiDropdownBox(), GuiSlider*(), GuiProgressBar(), GuiMessageBox()
*                         REVIEWED: GuiTextBox(), GuiSpinner(), GuiValueBox(), GuiLoadStyle()
*                         Replaced property INNER_PADDING by TEXT_PADDING, renamed some properties
*                         Added 8 new custom styles ready to use
*                         Multiple minor tweaks and bugs corrected
*       2.5 (28-May-2019) Implemented extended GuiTextBox(), GuiValueBox(), GuiSpinner()
*       2.3 (29-Apr-2019) Added rIcons auxiliar library and support for it, multiple controls reviewed
*                         Refactor all controls drawing mechanism to use control state
*       2.2 (05-Feb-2019) Added GuiScrollBar(), GuiScrollPanel(), reviewed GuiListView(), removed Gui*Ex() controls
*       2.1 (26-Dec-2018) Redesign of GuiCheckBox(), GuiComboBox(), GuiDropdownBox(), GuiToggleGroup() > Use combined text string
*                         Complete redesign of style system (breaking change)
*       2.0 (08-Nov-2018) Support controls guiLock and custom fonts, reviewed GuiComboBox(), GuiListView()...
*       1.9 (09-Oct-2018) Controls review: GuiGrid(), GuiTextBox(), GuiTextBoxMulti(), GuiValueBox()...
*       1.8 (01-May-2018) Lot of rework and redesign to align with rGuiStyler and rGuiLayout
*       1.5 (21-Jun-2017) Working in an improved styles system
*       1.4 (15-Jun-2017) Rewritten all GUI functions (removed useless ones)
*       1.3 (12-Jun-2017) Redesigned styles system
*       1.1 (01-Jun-2017) Complete review of the library
*       1.0 (07-Jun-2016) Converted to header-only by Ramon Santamaria.
*       0.9 (07-Mar-2016) Reviewed and tested by Albert Martos, Ian Eito, Sergio Martinez and Ramon Santamaria.
*       0.8 (27-Aug-2015) Initial release. Implemented by Kevin Gato, Daniel Nicolás and Ramon Santamaria.
*
*   CONTRIBUTORS:
*       Ramon Santamaria:   Supervision, review, redesign, update and maintenance...
*       Vlad Adrian:        Complete rewrite of GuiTextBox() to support extended features (2019)
*       Sergio Martinez:    Review, testing (2015) and redesign of multiple controls (2018)
*       Adria Arranz:       Testing and Implementation of additional controls (2018)
*       Jordi Jorba:        Testing and Implementation of additional controls (2018)
*       Albert Martos:      Review and testing of the library (2015)
*       Ian Eito:           Review and testing of the library (2015)
*       Kevin Gato:         Initial implementation of basic components (2014)
*       Daniel Nicolas:     Initial implementation of basic components (2014)
*
*
*   LICENSE: zlib/libpng
*
*   Copyright (c) 2014-2019 Ramon Santamaria (@raysan5)
*
*   This software is provided "as-is", without any express or implied warranty. In no event
*   will the authors be held liable for any damages arising from the use of this software.
*
*   Permission is granted to anyone to use this software for any purpose, including commercial
*   applications, and to alter it and redistribute it freely, subject to the following restrictions:
*
*     1. The origin of this software must not be misrepresented; you must not claim that you
*     wrote the original software. If you use this software in a product, an acknowledgment
*     in the product documentation would be appreciated but is not required.
*
*     2. Altered source versions must be plainly marked as such, and must not be misrepresented
*     as being the original software.
*
*     3. This notice may not be removed or altered from any source distribution.
*
**********************************************************************************************/

#ifndef RAYGUI_H
#define RAYGUI_H

#define RAYGUI_VERSION  "2.6-dev"

#if !defined(RAYGUI_STANDALONE)
    #include "raylib.h"
#endif

#define RAYGUIDEF
// #if defined(RAYGUI_IMPLEMENTATION)
//     #if defined(_WIN32) && defined(BUILD_LIBTYPE_SHARED)
//         #define RAYGUIDEF __declspec(dllexport) extern  // We are building raygui as a Win32 shared library (.dll).
//     #elif defined(_WIN32) && defined(USE_LIBTYPE_SHARED)
//         #define RAYGUIDEF __declspec(dllimport)         // We are using raygui as a Win32 shared library (.dll)
//     #else
//         #ifdef __cplusplus
//             #define RAYGUIDEF extern "C"        // Functions visible from other files (no name mangling of functions in C++)
//         #else
//             #define RAYGUIDEF extern            // Functions visible from other files
//         #endif
//     #endif
// #elif defined(RAYGUI_STATIC)
//     #define RAYGUIDEF static                    // Functions just visible to module including this file
// #endif

//----------------------------------------------------------------------------------
// Defines and Macros
//----------------------------------------------------------------------------------
#define NUM_CONTROLS                    16      // Number of standard controls
#define NUM_PROPS_DEFAULT               16      // Number of standard properties
#define NUM_PROPS_EXTENDED               8      // Number of extended properties

#define TEXTEDIT_CURSOR_BLINK_FRAMES    20      // Text edit controls cursor blink timming

//----------------------------------------------------------------------------------
// Types and Structures Definition
// NOTE: Some types are required for RAYGUI_STANDALONE usage
//----------------------------------------------------------------------------------
#if defined(RAYGUI_STANDALONE)
    #ifndef __cplusplus
    // Boolean type
        #ifndef true
            typedef enum { false, true } bool;
        #endif
    #endif

    // Vector2 type
    typedef struct Vector2 {
        float x;
        float y;
    } Vector2;

    // Vector3 type
    typedef struct Vector3 {
        float x;
        float y;
        float z;
    } Vector3;

    // Color type, RGBA (32bit)
    typedef struct Color {
        unsigned char r;
        unsigned char g;
        unsigned char b;
        unsigned char a;
    } Color;

    // Rectangle type
    typedef struct Rectangle {
        int x;
        int y;
        int width;
        int height;
    } Rectangle;

    // Texture2D type
    // NOTE: It should be provided by user
    typedef struct Texture2D Texture2D;

    // Font type
    // NOTE: It should be provided by user
    typedef struct Font Font;
#endif

#if defined(RAYGUI_TEXTBOX_EXTENDED)
// Gui text box state data
typedef struct GuiTextBoxState {
    int cursor;      // Cursor position in text
    int start;       // Text start position (from where we begin drawing the text)
    int index;       // Text start index (index inside the text of `start` always in sync)
    int select;      // Marks position of cursor when selection has started
} GuiTextBoxState;
#endif

// Style property
typedef struct GuiStyleProp {
    unsigned short controlId;
    unsigned short propertyId;
    int propertyValue;
} GuiStyleProp;

// Gui control state
typedef enum {
    GUI_STATE_NORMAL = 0,
    GUI_STATE_FOCUSED,
    GUI_STATE_PRESSED,
    GUI_STATE_DISABLED,
} GuiControlState;

// Gui control text alignment
typedef enum {
    GUI_TEXT_ALIGN_LEFT = 0,
    GUI_TEXT_ALIGN_CENTER,
    GUI_TEXT_ALIGN_RIGHT,
} GuiTextAlignment;

// Gui controls
typedef enum {
    DEFAULT = 0,
    LABEL,          // LABELBUTTON
    BUTTON,         // IMAGEBUTTON
    TOGGLE,         // TOGGLEGROUP
    SLIDER,         // SLIDERBAR
    PROGRESSBAR,
    CHECKBOX,
    COMBOBOX,
    DROPDOWNBOX,
    TEXTBOX,        // TEXTBOXMULTI
    VALUEBOX,
    SPINNER,
    LISTVIEW,
    COLORPICKER,
    SCROLLBAR,
    STATUSBAR
} GuiControl;

// Gui base properties for every control
typedef enum {
    BORDER_COLOR_NORMAL = 0,
    BASE_COLOR_NORMAL,
    TEXT_COLOR_NORMAL,
    BORDER_COLOR_FOCUSED,
    BASE_COLOR_FOCUSED,
    TEXT_COLOR_FOCUSED,
    BORDER_COLOR_PRESSED,
    BASE_COLOR_PRESSED,
    TEXT_COLOR_PRESSED,
    BORDER_COLOR_DISABLED,
    BASE_COLOR_DISABLED,
    TEXT_COLOR_DISABLED,
    BORDER_WIDTH,
    TEXT_PADDING,
    TEXT_ALIGNMENT,
    RESERVED
} GuiControlProperty;

// Gui extended properties depend on control
// NOTE: We reserve a fixed size of additional properties per control

// DEFAULT properties
typedef enum {
    TEXT_SIZE = 16,
    TEXT_SPACING,
    LINE_COLOR,
    BACKGROUND_COLOR,
} GuiDefaultProperty;

// Label
//typedef enum { } GuiLabelProperty;

// Button
//typedef enum { } GuiButtonProperty;

// Toggle / ToggleGroup
typedef enum {
    GROUP_PADDING = 16,
} GuiToggleProperty;

// Slider / SliderBar
typedef enum {
    SLIDER_WIDTH = 16,
    SLIDER_PADDING
} GuiSliderProperty;

// ProgressBar
typedef enum { 
    PROGRESS_PADDING = 16,
} GuiProgressBarProperty;

// CheckBox
typedef enum {
    CHECK_PADDING = 16
} GuiCheckBoxProperty;

// ComboBox
typedef enum {
    COMBO_BUTTON_WIDTH = 16,
    COMBO_BUTTON_PADDING
} GuiComboBoxProperty;

// DropdownBox
typedef enum {
    ARROW_PADDING = 16,
    DROPDOWN_ITEMS_PADDING
} GuiDropdownBoxProperty;

// TextBox / TextBoxMulti / ValueBox / Spinner
typedef enum {
    TEXT_INNER_PADDING = 16,
    TEXT_LINES_PADDING,
    COLOR_SELECTED_FG,
    COLOR_SELECTED_BG
} GuiTextBoxProperty;

// Spinner
typedef enum {
    SPIN_BUTTON_WIDTH = 16,
    SPIN_BUTTON_PADDING,
} GuiSpinnerProperty;

// ScrollBar
typedef enum {
    ARROWS_SIZE = 16,
    ARROWS_VISIBLE,
    SCROLL_SLIDER_PADDING,
    SCROLL_SLIDER_SIZE,
    SCROLL_PADDING,
    SCROLL_SPEED,
} GuiScrollBarProperty;

// ScrollBar side
typedef enum {
    SCROLLBAR_LEFT_SIDE = 0,
    SCROLLBAR_RIGHT_SIDE
} GuiScrollBarSide;

// ListView
typedef enum {
    LIST_ITEMS_HEIGHT = 16,
    LIST_ITEMS_PADDING,
    SCROLLBAR_WIDTH,
    SCROLLBAR_SIDE,
} GuiListViewProperty;

// ColorPicker
typedef enum {
    COLOR_SELECTOR_SIZE = 16,
    HUEBAR_WIDTH,                  // Right hue bar width
    HUEBAR_PADDING,                // Right hue bar separation from panel
    HUEBAR_SELECTOR_HEIGHT,        // Right hue bar selector height
    HUEBAR_SELECTOR_OVERFLOW       // Right hue bar selector overflow
} GuiColorPickerProperty;

//----------------------------------------------------------------------------------
// Global Variables Definition
//----------------------------------------------------------------------------------
// ...

//----------------------------------------------------------------------------------
// Module Functions Declaration
//----------------------------------------------------------------------------------

// Global gui modification functions
RAYGUIDEF void GuiEnable(void);                                         // Enable gui controls (global state)
RAYGUIDEF void GuiDisable(void);                                        // Disable gui controls (global state)
RAYGUIDEF void GuiLock(void);                                           // Lock gui controls (global state)
RAYGUIDEF void GuiUnlock(void);                                         // Unlock gui controls (global state)
RAYGUIDEF void GuiFade(float alpha);                                    // Set gui controls alpha (global state), alpha goes from 0.0f to 1.0f

RAYGUIDEF void GuiSetState(int state);                                  // Set gui state (global state)
RAYGUIDEF int GuiGetState(void);                                        // Get gui state (global state)

RAYGUIDEF void GuiSetFont(Font font);                                   // Set gui custom font (global state)
RAYGUIDEF Font GuiGetFont(void);                                        // Get gui custom font (global state)

// Style set/get functions
RAYGUIDEF void GuiSetStyle(int control, int property, int value);       // Set one style property
RAYGUIDEF int GuiGetStyle(int control, int property);                   // Get one style property

#if defined(RAYGUI_TEXTBOX_EXTENDED)
// GuiTextBox() extended functions
RAYGUIDEF void GuiTextBoxSetActive(Rectangle bounds);                   // Sets the active textbox
RAYGUIDEF Rectangle GuiTextBoxGetActive(void);                          // Get bounds of active textbox
RAYGUIDEF void GuiTextBoxSetCursor(int cursor);                         // Set cursor position of active textbox
RAYGUIDEF int GuiTextBoxGetCursor(void);                                // Get cursor position of active textbox
RAYGUIDEF void GuiTextBoxSetSelection(int start, int length);           // Set selection of active textbox
RAYGUIDEF Vector2 GuiTextBoxGetSelection(void);                         // Get selection of active textbox (x - selection start  y - selection length)
RAYGUIDEF bool GuiTextBoxIsActive(Rectangle bounds);                    // Returns true if a textbox control with specified `bounds` is the active textbox
RAYGUIDEF GuiTextBoxState GuiTextBoxGetState(void);                     // Get state for the active textbox
RAYGUIDEF void GuiTextBoxSetState(GuiTextBoxState state);               // Set state for the active textbox (state must be valid else things will break)
RAYGUIDEF void GuiTextBoxSelectAll(const char *text);                   // Select all characters in the active textbox (same as pressing `CTRL` + `A`)
RAYGUIDEF void GuiTextBoxCopy(const char *text);                        // Copy selected text to clipboard from the active textbox (same as pressing `CTRL` + `C`)
RAYGUIDEF void GuiTextBoxPaste(char *text, int textSize);               // Paste text from clipboard into the textbox (same as pressing `CTRL` + `V`)
RAYGUIDEF void GuiTextBoxCut(char *text);                               // Cut selected text in the active textbox and copy it to clipboard (same as pressing `CTRL` + `X`)
RAYGUIDEF int GuiTextBoxDelete(char *text, int length, bool before);    // Deletes a character or selection before from the active textbox (depending on `before`). Returns bytes deleted.
RAYGUIDEF int GuiTextBoxGetByteIndex(const char *text, int start, int from, int to); // Get the byte index for a character starting at position `from` with index `start` until position `to`.
#endif

// Container/separator controls, useful for controls organization
RAYGUIDEF bool GuiWindowBox(Rectangle bounds, const char *title);                                       // Window Box control, shows a window that can be closed
RAYGUIDEF void GuiGroupBox(Rectangle bounds, const char *text);                                         // Group Box control with text name
RAYGUIDEF void GuiLine(Rectangle bounds, const char *text);                                             // Line separator control, could contain text
RAYGUIDEF void GuiPanel(Rectangle bounds);                                                              // Panel control, useful to group controls
RAYGUIDEF Rectangle GuiScrollPanel(Rectangle bounds, Rectangle content, Vector2 *scroll);               // Scroll Panel control

// Basic controls set
RAYGUIDEF void GuiLabel(Rectangle bounds, const char *text);                                            // Label control, shows text
RAYGUIDEF bool GuiButton(Rectangle bounds, const char *text);                                           // Button control, returns true when clicked
RAYGUIDEF bool GuiLabelButton(Rectangle bounds, const char *text);                                      // Label button control, show true when clicked
RAYGUIDEF bool GuiImageButton(Rectangle bounds, const char *text, Texture2D texture);                   // Image button control, returns true when clicked
RAYGUIDEF bool GuiImageButtonEx(Rectangle bounds, const char *text, Texture2D texture, Rectangle texSource);    // Image button extended control, returns true when clicked
RAYGUIDEF bool GuiToggle(Rectangle bounds, const char *text, bool active);                              // Toggle Button control, returns true when active
RAYGUIDEF int GuiToggleGroup(Rectangle bounds, const char *text, int active);                           // Toggle Group control, returns active toggle index
RAYGUIDEF bool GuiCheckBox(Rectangle bounds, const char *text, bool checked);                           // Check Box control, returns true when active
RAYGUIDEF int GuiComboBox(Rectangle bounds, const char *text, int active);                              // Combo Box control, returns selected item index
RAYGUIDEF bool GuiDropdownBox(Rectangle bounds, const char *text, int *active, bool editMode);          // Dropdown Box control, returns selected item
RAYGUIDEF bool GuiSpinner(Rectangle bounds, const char *text, int *value, int minValue, int maxValue, bool editMode);     // Spinner control, returns selected value
RAYGUIDEF bool GuiValueBox(Rectangle bounds, const char *text, int *value, int minValue, int maxValue, bool editMode);    // Value Box control, updates input text with numbers
RAYGUIDEF bool GuiTextBox(Rectangle bounds, char *text, int textSize, bool editMode);                   // Text Box control, updates input text
RAYGUIDEF bool GuiTextBoxMulti(Rectangle bounds, char *text, int textSize, bool editMode);              // Text Box control with multiple lines
RAYGUIDEF float GuiSlider(Rectangle bounds, const char *textLeft, const char *textRight, float value, float minValue, float maxValue);       // Slider control, returns selected value
RAYGUIDEF float GuiSliderBar(Rectangle bounds, const char *textLeft, const char *textRight, float value, float minValue, float maxValue);    // Slider Bar control, returns selected value
RAYGUIDEF float GuiProgressBar(Rectangle bounds, const char *textLeft, const char *textRight, float value, float minValue, float maxValue);  // Progress Bar control, shows current progress value
RAYGUIDEF void GuiStatusBar(Rectangle bounds, const char *text);                                        // Status Bar control, shows info text
RAYGUIDEF void GuiDummyRec(Rectangle bounds, const char *text);                                         // Dummy control for placeholders
RAYGUIDEF int GuiScrollBar(Rectangle bounds, int value, int minValue, int maxValue);                    // Scroll Bar control
RAYGUIDEF Vector2 GuiGrid(Rectangle bounds, float spacing, int subdivs);                                // Grid control

// Advance controls set
RAYGUIDEF int GuiListView(Rectangle bounds, const char *text, int *scrollIndex, int active);            // List View control, returns selected list item index
RAYGUIDEF int GuiListViewEx(Rectangle bounds, const char **text, int count, int *focus, int *scrollIndex, int active);      // List View with extended parameters
RAYGUIDEF int GuiMessageBox(Rectangle bounds, const char *title, const char *message, const char *buttons);                 // Message Box control, displays a message
RAYGUIDEF int GuiTextInputBox(Rectangle bounds, const char *title, const char *message, const char *buttons, char *text);   // Text Input Box control, ask for text
RAYGUIDEF Color GuiColorPicker(Rectangle bounds, Color color);                                          // Color Picker control

// Styles loading functions
RAYGUIDEF void GuiLoadStyle(const char *fileName);              // Load style file (.rgs)
RAYGUIDEF void GuiLoadStyleDefault(void);                       // Load style default over global style

/*
typedef GuiStyle (unsigned int *)
RAYGUIDEF GuiStyle LoadGuiStyle(const char *fileName);          // Load style from file (.rgs)
RAYGUIDEF void UnloadGuiStyle(GuiStyle style);                  // Unload style
*/

RAYGUIDEF const char *GuiIconText(int iconId, const char *text); // Get text with icon id prepended

#endif // RAYGUI_H
