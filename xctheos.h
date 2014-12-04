//
//  xctheos.h
//  Xcode|Theos
//
//  Created by Adam Bell on 2014-03-24.
//  Copyright (c) 2014 Adam Bell. All rights reserved.
//

#ifdef __OBJC__
    #define _STRING(stuff) #stuff
    #define STRING(stuff) _STRING(stuff)

    #define _CONCAT(stuff, otherstuff) stuff ## otherstuff
    #define CONCAT(stuff, otherstuff) _CONCAT(stuff, otherstuff)
    #define UNIQUE_SUFFIX(stuff) CONCAT(stuff, __COUNTER__)

    #ifdef __LOGOS_H
        #define CONFIG(stuff) %config(stuff)
        #define INIT(stuff) %init(stuff)
        #define GROUP(stuff) %group stuff
        #define END_GROUP() %end
        #define HOOK(stuff) %hook stuff
        #define HOOK_AND_DECLARE(stuff, superclass) %hook stuff
        #define NEW(...)  %new
        #define END() %end
        #define ORIG(...) %orig(__VA_ARGS__)
        #define ORIG_T(...) %orig(__VA_ARGS__)
        #define GET_CLASS(stuff) %c(stuff)
        #define SUBCLASS(stuff, superclass) %subclass stuff : superclass
        #define END_SUBCLASS() %end
        #define CTOR(hax) %ctor hax
    #else
        #import <objc/runtime.h>

        #define CLANG_NO_U _Pragma("clang diagnostic push") _Pragma("clang diagnostic ignored \"-Wobjc-protocol-method-implementation\"") _Pragma("clang diagnostic ignored \"-Wunused-function\"")
        #define CLANG_NO_U_END _Pragma("clang diagnostic pop") _Pragma("clang diagnostic pop")

        #define CONFIG(stuff)
        #define INIT(stuff)
        #define GROUP(stuff)
        #define END_GROUP()
        #define HOOK(stuff) CLANG_NO_U @interface stuff(UNIQUE_SUFFIX(hax)) @end @implementation stuff (UNIQUE_SUFFIX(hax))
        #define HOOK_AND_DECLARE(stuff, superclass) CLANG_NO_U @interface stuff : superclass @end @implementation stuff
        #define NEW(...)
        #define END() @end CLANG_NO_U_END
        #define ORIG(...) nil
        #define ORIG_T(...) 0
        #define GET_CLASS(stuff) objc_getClass(STRING(stuff))
        #define SUBCLASS(stuff, superclass) @interface stuff : superclass @end @implementation stuff
        #define END_SUBCLASS() @end
        #define CTOR(hax) CLANG_NO_U static void inline stuff() hax CLANG_NO_U_END
    #endif
#endif
