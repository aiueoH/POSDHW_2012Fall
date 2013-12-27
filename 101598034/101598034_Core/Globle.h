#ifndef GLOBLE_H_
#define GLOBLE_H_


#include <string>
#include <map>

using namespace std;
///////////////////////////////////////////////////////////////////////////
// GUI
///////////////////////////////////////////////////////////////////////////
// 複製偏移
const int DELTA_X = 50;
const int DELTA_Y = 50;
// 畫布大小
const int PANEL_WIDTH = 5000;
const int PANEL_HEIGHT = 5000;
// 基本大小
const int GRAPH_WIDTH = 30;
const int GRAPH_HEIGHT = 30;
// edge
const int EDGE_ARROW_LENGTH = 5;
const int EDGE_COLLISION_SIZR = 10;
const int EDGE_CONNECTION_POINT_WIDTH = 10;
const int EDGE_CONNECTION_POINT_HEIGHT = 10;
// activity
const int ACTIVITY_TEXT_PADDING = 10;
const int ACTIVITY_REC_X_ROUND = 10;
const int ACTIVITY_REC_Y_ROUND = 10;
// text
const int TEXT_LENGTH_PER_CHAR = 10;
// char 轉換為 string 的長度
const int CHAR_TO_STRING_LENTH = 1;
// string 中第一個 char 的 index
const int FIRST_CHAR_INDEX_OF_STRING = 0;
// find 不到東西時回傳的值
const int INDEX_OF_NOT_FOUND = -1;
// type name
const string INITIAL_NODE_TYPE_NAME = "Initial Node";
const string FINAL_NODE_TYPE_NAME = "Final Node";
const string ACTIVITY_TYPE_NAME = "Activity";
const string EDGE_TYPE_NAME = "Edge";
const string DECISION_NODE_TYPE_NAME = "Decision Node";
// ActivityDiagramTable
const string TABLE_HEADER_NAME_TYPE = "Type";
const string TABLE_HEADER_NAME_TEXT = "Text";
const int TABLE_HEADER_COUNT = 2;
const int TABLE_HEADER_INDEX_TYPE = 0;
const int TABLE_HEADER_INDEX_TEXT = 1;
const string TABLE_LABEL_TEXT = "Glyphs";
const int TABLE_LABEL_HEIGHT = 30;
const int TABLE_LINE_WIDTH = 2;

enum GLYPH_TYPE {INITIAL_NODE = 'I', FINAL_NODE = 'F', ACTIVITY = 'A', EDGE = 'E', DECISION_NODE = 'D', ERROR_GLYPH = 'R'};
enum DRAW_INSTRUCTION_TYPE {SET_PEN_COLOR, SET_BRUSH, DRAW_LINE, DRAW_ELLIPSE, DRAW_ROUNDEDRECT, DRAW_TEXT};
enum DRAW_INSTRUCTION_PEN_STYLE {NOBRUSH = 0, BLACK = 2, WHITE = 3, GRAY = 5, BLUE = 9};

#endif