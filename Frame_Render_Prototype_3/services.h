#ifndef __SERVICES_H__
#define __SERVICES_H__

#include "cursorService.h"
#include "highlightService.h"
#include "lineDrawService.h"
#include "textColorService.h"
#include "userInputService.h"

namespace Services {
static CursorService* _CursorServiceHandle = CursorService::getService();
static LineDrawService* _LineDrawServiceHandle = LineDrawService::getService();
static TextColorService* _TextColorServiceHandle = TextColorService::getService();
static HighlightService* _HighlightServiceHandle = HighlightService::getService();
static UserInputService* _UserInputServiceHandle = UserInputService::getService();
}  // namespace Services

#endif