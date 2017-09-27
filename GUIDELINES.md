# Contributing Guidelines

---
For the most part you're free to format your code as you wish. Same goes for issues, pull requests, and commits. However there are a few things I'd strongly recommend you do. If you chose not to you probably won't be docked points but it'd be appreciated if you followed these guidelines.


## 1. Issues
Before you submit an issue, make sure it isn't because of a broken code. Disable each code one by one to determine which code might be faulty. If there is no consistent code that is causing the bug or the codes work with NetCheat PS3 then submit an issue.

Please use the following template when submitting an in-game related issue.
```
FW: 4.81 REBUG DEX
API: CCAPI / TMAPI / PS3MAPI
GAME: Assassin's Creed III
VERSION: Artemis PS3 Lite 1.0.1-alpha
CODE:
Provide a code if a code is causing the issue.

Then just provide context here.
```

For issues when in the GUI follow this template.
```
FW: 4.81 REBUG DEX
VERSION: Artemis PS3 Lite 1.0.1-alpha

Context.
```


## 2. Commenting Public Class Members
In general your code should be well documented to help everyone understand exactly what it does. Most importantly, within class declarations, each public method needs adequate comments to explain what it does, how each argument is used, and what it returns. However if you're repeating yourself telling us `PrintLine(char * line)` prints a line... Just don't document it.

```
/*
 * Icon.cpp
 *
 * Draws an icon and a label under it. Scales well between 16:9 and 4:3.
 */

class Icon
{
    Icon(Mini2D::Image icon, std::wstring label);
    ~Icon();

    /*
     * SuperComplexDrawAnimation9000:
     *   Draws the icon along a path set by 'start' and 'end' for 'timeSpan' number of milliseconds
     *
     * return:
     *   Returns true if successful
     */
    bool SuperComplexDrawAnimation9000(Mini2D::Vector2 start, Mini2D::Vector2 end, float timeSpan);
}
```

This is a good example of adequate documentation. We've explained what this class does at the top so adding a comment to explain what the constructor does it unnecessary (though perfectly acceptable). Each argument of the constructor is also sensible named and the purpose of each can easily be deduced. The `SuperComplexDrawAnimation9000` method isn't as easy to understand without an explanation. The comment above its declaration provides enough information for another contributor to understand its function and how to use it. You do not have to format it like that. Just have it make sense.


## 3. Variable Naming Conventions
 * Globals, constants, macros, and enum members should be completely capitalized. If it's a constant reference type it should NOT be capitalized (unless it's a global variable).
 * Public variables should begin with a capital letter.
 * Private variables should be prefixed with an underscore.
 * Everything else in the function scope or lower can be named as you wish.
```
class Example
{
    public:
        const int THIS_IS_A_CONST_VAR = 1;
        const char * THIS_IS_A_CONST_REF_AND_NOT_OK = 0;
        int ThisIsAPublicVar = 1;
        int Thisisalsoapublicvar = 1;

    private:
        int _thisIsAPrivateVar = 1;
        const int THIS_IS_OKAY_TOO = 1;
        int PleaseDoNotDoThis = 0;
}
```

Naming variables consistently based on protection level and scope improves class organization and readability for everyone.

## 4. Indentation and Alignment
You can use tabs or spaces. But if you plan on aligning code at a specific line index to make your code look all pretty-like.. please use spaces. If you use tabs for something like that, it will look different between text editors and on Github.
```cpp
// This looks great because spaces
float FONT_SMALL =     0.0105;
float FONT_MEDIUM =    FONT_SMALL * 1.5;
float FONT_LARGE =     FONT_MEDIUM * 1.5;

Vector2 LOC_CENTER =   Vector2(0.5, 0.5);
Vector2 DIM_FULL =     Vector2(1.0, 1.0);

// But with tabs...
float FONT_SMALL =         0.0105;
float FONT_MEDIUM =    FONT_SMALL * 1.5;
float FONT_LARGE =             FONT_MEDIUM * 1.5;

Vector2 LOC_CENTER =   Vector2(0.5, 0.5);
Vector2 DIM_FULL = Vector2(1.0, 1.0);
```
