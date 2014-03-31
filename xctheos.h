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
        #define CTOR() %ctor
    #else
        #import <objc/runtime.h>

        #define STFU_CLANG _Pragma("clang diagnostic push") _Pragma("clang diagnostic ignored \"-Wobjc-protocol-method-implementation\"")
        #define END_STFU_CLANG

        #define CONFIG(stuff)
        #define INIT(stuff)
        #define GROUP(stuff)
        #define END_GROUP()
        #define HOOK(stuff) STFU_CLANG @interface stuff(UNIQUE_SUFFIX(hax)) @end @implementation stuff (UNIQUE_SUFFIX(hax))
        #define HOOK_AND_DECLARE(stuff, superclass) STFU_CLANG @interface stuff : superclass @end @implementation stuff
        #define NEW(...)
        #define END() @end END_STFU_CLANG
        #define ORIG(...) nil
        #define ORIG_T(...) 0
        #define GET_CLASS(stuff) objc_getClass(STRING(stuff))
        #define SUBCLASS(stuff, superclass) @interface stuff : superclass @end @implementation stuff
        #define END_SUBCLASS() @end
        #define CTOR() static void inline stuff()
    #endif
#endif
