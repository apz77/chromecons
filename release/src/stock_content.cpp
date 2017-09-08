#include "stock_content.h"

std::string getStyleTag() {
    return "<style>"
           "body {background: #f5f7f9; margin: 0; padding: 0;}"
           ".header-container { \
               position: relative;\
               height: 100px;\
               box-shadow: 0 2px 10px 0 rgba(52,56,70,0.15);\
               z-index: 2;\
               width: 100%;\
               text-align: center;\
               background: linear-gradient(to right, #fff 50%, #2a2d38 50%);"
            "} "
            ".header {"
                "display: inline-block;"
                "width: 1250px;"
                "position: relative;"
            "} "
            ".logo {"
                "position: absolute;"
                "top: 12px;"
                "left: 78px;"
                "width: 62px;"
                "z-index: 3;"
            "} "
            ".logo svg {"
                "width: 62px;"
                "height:93px"
            "} "
            ".text-logo {"
                "position: absolute;"
                "width: 183px;"
                "top: 40px;"
                "left: 168px;"
            "} "
            ".right-part {"
                "float: right;"
                "width: 60%;"
                "padding-right: 120px;"
                "color: #848aa2;"
                "height: 100px;"
                "background-color: #2a2d38;"
                "margin: 0;"
                "position: relative;"
            "} "
            ".right-part:before {"
                "content: \"\";"
                "position: absolute;"
                "border-bottom: 100px solid #2a2d38;"
                "border-left: 40px solid transparent;"
                "border-right: 40px solid transparent;"
                "left: 0;"
                "transform: translateX(-50%);"
                "top: 0;"
                "z-index: 2;"
            "} "
            ".triangle {"
                "position: absolute;"
                "width: 100px;"
                "height: 25px;"
                "left: 59px;"
                "bottom: -25px;"
            "}"
            ".content {"
                "max-width: 700px;"
                "margin-left: auto;"
                "margin-right: auto;"
                "margin-top: 50px;"
            "}"
            "h1 {"
                "text-align: center;"
                "font-size: 24px;"
            "}"
            ".msg {"
                "text-align: center;"
            "}"
        "</style>";
}

std::string getLogo() {
    return "<svg id=\"Logo_dark\" data-name=\"Logo dark\" xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\"\n"
"     width=\"36\" height=\"36\" viewBox=\"7 1 24 36\">\n"
"    <defs>\n"
"        <style>\n"
"            .logo-black-cls-1, .logo-black-cls-2, .logo-black-cls-4, .logo-black-cls-5 {\n"
"            fill: #313331;\n"
"            }\n"
"\n"
"            .logo-black-cls-1, .logo-black-cls-2, .logo-black-cls-3, .logo-black-cls-4, .logo-black-cls-5 {\n"
"            fill-rule: evenodd;\n"
"            }\n"
"\n"
"            .logo-black-cls-1 {\n"
"            filter: url(#logo-black-filter);\n"
"            }\n"
"\n"
"            .logo-black-cls-2 {\n"
"            filter: url(#logo-black-filter-2);\n"
"            }\n"
"\n"
"            .logo-black-cls-3 {\n"
"            fill: #3e4d5d;\n"
"            filter: url(#logo-black-filter-3);\n"
"            }\n"
"\n"
"            .logo-black-cls-4 {\n"
"            filter: url(#logo-black-filter-4);\n"
"            }\n"
"\n"
"            .logo-black-cls-5 {\n"
"            filter: url(#logo-black-filter-5);\n"
"            }\n"
"        </style>\n"
"        <filter id=\"logo-black-filter\" x=\"7\" y=\"14\" width=\"24\" height=\"23\" filterUnits=\"userSpaceOnUse\">\n"
"            <feImage preserveAspectRatio=\"none\" x=\"7\" y=\"14\" width=\"24\" height=\"23\" result=\"image\"\n"
"                     xlink:href=\"data:image/svg+xml;base64,PHN2ZyB4bWxucz0iaHR0cDovL3d3dy53My5vcmcvMjAwMC9zdmciIHhtbG5zOnhsaW5rPSJodHRwOi8vd3d3LnczLm9yZy8xOTk5L3hsaW5rIiB3aWR0aD0iMjQiIGhlaWdodD0iMjMiIHZpZXdCb3g9IjAgMCAyNCAyMyI+CiAgPGRlZnM+CiAgICA8c3R5bGU+CiAgICAgIC5jbHMtMSB7CiAgICAgICAgZmlsbDogdXJsKCNsaW5lYXItZ3JhZGllbnQpOwogICAgICB9CiAgICA8L3N0eWxlPgogICAgPGxpbmVhckdyYWRpZW50IGlkPSJsaW5lYXItZ3JhZGllbnQiIHgxPSI5Ljk3MiIgeTE9IjIzIiB4Mj0iMTQuMDI4IiBncmFkaWVudFVuaXRzPSJ1c2VyU3BhY2VPblVzZSI+CiAgICAgIDxzdG9wIG9mZnNldD0iMCIgc3RvcC1jb2xvcj0iIzIwMjEyMCIvPgogICAgICA8c3RvcCBvZmZzZXQ9IjAuMTAyIiBzdG9wLWNvbG9yPSIjMjAyMTIwIi8+CiAgICAgIDxzdG9wIG9mZnNldD0iMC41IiBzdG9wLWNvbG9yPSIjNmM2YzZjIi8+CiAgICAgIDxzdG9wIG9mZnNldD0iMC44OTgiIHN0b3AtY29sb3I9IiMyMDIxMjAiLz4KICAgICAgPHN0b3Agb2Zmc2V0PSIxIiBzdG9wLWNvbG9yPSIjMjAyMTIwIi8+CiAgICA8L2xpbmVhckdyYWRpZW50PgogIDwvZGVmcz4KICA8cmVjdCBjbGFzcz0iY2xzLTEiIHdpZHRoPSIyNCIgaGVpZ2h0PSIyMyIvPgo8L3N2Zz4K\"/>\n"
"            <feComposite result=\"composite\" operator=\"in\" in2=\"SourceGraphic\"/>\n"
"            <feBlend result=\"blend\" in2=\"SourceGraphic\"/>\n"
"        </filter>\n"
"        <filter id=\"logo-black-filter-2\" x=\"9\" y=\"17\" width=\"20\" height=\"17\" filterUnits=\"userSpaceOnUse\">\n"
"            <feImage preserveAspectRatio=\"none\" x=\"9\" y=\"17\" width=\"20\" height=\"17\" result=\"image\"\n"
"                     xlink:href=\"data:image/svg+xml;base64,PHN2ZyB4bWxucz0iaHR0cDovL3d3dy53My5vcmcvMjAwMC9zdmciIHhtbG5zOnhsaW5rPSJodHRwOi8vd3d3LnczLm9yZy8xOTk5L3hsaW5rIiB3aWR0aD0iMjAiIGhlaWdodD0iMTciIHZpZXdCb3g9IjAgMCAyMCAxNyI+CiAgPGRlZnM+CiAgICA8c3R5bGU+CiAgICAgIC5jbHMtMSB7CiAgICAgICAgZmlsbDogdXJsKCNsaW5lYXItZ3JhZGllbnQpOwogICAgICB9CiAgICA8L3N0eWxlPgogICAgPGxpbmVhckdyYWRpZW50IGlkPSJsaW5lYXItZ3JhZGllbnQiIHgxPSI4LjUwMSIgeTE9IjE3IiB4Mj0iMTEuNDk5IiBncmFkaWVudFVuaXRzPSJ1c2VyU3BhY2VPblVzZSI+CiAgICAgIDxzdG9wIG9mZnNldD0iMCIgc3RvcC1jb2xvcj0iIzZjNmM2YyIvPgogICAgICA8c3RvcCBvZmZzZXQ9IjAuMzk4IiBzdG9wLWNvbG9yPSIjMjAyMTIwIi8+CiAgICAgIDxzdG9wIG9mZnNldD0iMC41IiBzdG9wLWNvbG9yPSIjMjAyMTIwIi8+CiAgICAgIDxzdG9wIG9mZnNldD0iMC42MDIiIHN0b3AtY29sb3I9IiMyMDIxMjAiLz4KICAgICAgPHN0b3Agb2Zmc2V0PSIxIiBzdG9wLWNvbG9yPSIjNmM2YzZjIi8+CiAgICA8L2xpbmVhckdyYWRpZW50PgogIDwvZGVmcz4KICA8cmVjdCBjbGFzcz0iY2xzLTEiIHdpZHRoPSIyMCIgaGVpZ2h0PSIxNyIvPgo8L3N2Zz4K\"/>\n"
"            <feComposite result=\"composite\" operator=\"in\" in2=\"SourceGraphic\"/>\n"
"            <feBlend result=\"blend\" in2=\"SourceGraphic\"/>\n"
"        </filter>\n"
"        <filter id=\"logo-black-filter-3\" x=\"12\" y=\"19\" width=\"14\" height=\"12\" filterUnits=\"userSpaceOnUse\">\n"
"            <feImage preserveAspectRatio=\"none\" x=\"12\" y=\"19\" width=\"14\" height=\"12\" result=\"image\"\n"
"                     xlink:href=\"data:image/svg+xml;base64,PHN2ZyB4bWxucz0iaHR0cDovL3d3dy53My5vcmcvMjAwMC9zdmciIHhtbG5zOnhsaW5rPSJodHRwOi8vd3d3LnczLm9yZy8xOTk5L3hsaW5rIiB3aWR0aD0iMTQiIGhlaWdodD0iMTIiIHZpZXdCb3g9IjAgMCAxNCAxMiI+CiAgPGRlZnM+CiAgICA8c3R5bGU+CiAgICAgIC5jbHMtMSB7CiAgICAgICAgZmlsbDogdXJsKCNsaW5lYXItZ3JhZGllbnQpOwogICAgICB9CiAgICA8L3N0eWxlPgogICAgPGxpbmVhckdyYWRpZW50IGlkPSJsaW5lYXItZ3JhZGllbnQiIHgxPSIxMS4yMDEiIHgyPSIyLjc5OSIgeTI9IjEyIiBncmFkaWVudFVuaXRzPSJ1c2VyU3BhY2VPblVzZSI+CiAgICAgIDxzdG9wIG9mZnNldD0iMCIgc3RvcC1jb2xvcj0iI2ZjMmMxYSIvPgogICAgICA8c3RvcCBvZmZzZXQ9IjAuMjI0IiBzdG9wLWNvbG9yPSIjZmMyYzFhIi8+CiAgICAgIDxzdG9wIG9mZnNldD0iMC43MTciIHN0b3AtY29sb3I9IiM4MzE2MDgiLz4KICAgICAgPHN0b3Agb2Zmc2V0PSIxIiBzdG9wLWNvbG9yPSIjODMxNjA4Ii8+CiAgICA8L2xpbmVhckdyYWRpZW50PgogIDwvZGVmcz4KICA8cmVjdCBjbGFzcz0iY2xzLTEiIHdpZHRoPSIxNCIgaGVpZ2h0PSIxMiIvPgo8L3N2Zz4K\"/>\n"
"            <feComposite result=\"composite\" operator=\"in\" in2=\"SourceGraphic\"/>\n"
"            <feBlend result=\"blend\" in2=\"SourceGraphic\"/>\n"
"        </filter>\n"
"        <filter id=\"logo-black-filter-4\" x=\"7\" y=\"1\" width=\"24\" height=\"16\" filterUnits=\"userSpaceOnUse\">\n"
"            <feImage preserveAspectRatio=\"none\" x=\"7\" y=\"1\" width=\"24\" height=\"16\" result=\"image\"\n"
"                     xlink:href=\"data:image/svg+xml;base64,PHN2ZyB4bWxucz0iaHR0cDovL3d3dy53My5vcmcvMjAwMC9zdmciIHhtbG5zOnhsaW5rPSJodHRwOi8vd3d3LnczLm9yZy8xOTk5L3hsaW5rIiB3aWR0aD0iMjQiIGhlaWdodD0iMTYiIHZpZXdCb3g9IjAgMCAyNCAxNiI+CiAgPGRlZnM+CiAgICA8c3R5bGU+CiAgICAgIC5jbHMtMSB7CiAgICAgICAgZmlsbDogdXJsKCNsaW5lYXItZ3JhZGllbnQpOwogICAgICB9CiAgICA8L3N0eWxlPgogICAgPGxpbmVhckdyYWRpZW50IGlkPSJsaW5lYXItZ3JhZGllbnQiIHgxPSIxMC41ODkiIHkxPSIxNiIgeDI9IjEzLjQxMSIgZ3JhZGllbnRVbml0cz0idXNlclNwYWNlT25Vc2UiPgogICAgICA8c3RvcCBvZmZzZXQ9IjAiIHN0b3AtY29sb3I9IiM2YzZjNmMiLz4KICAgICAgPHN0b3Agb2Zmc2V0PSIwLjM5OCIgc3RvcC1jb2xvcj0iIzIwMjEyMCIvPgogICAgICA8c3RvcCBvZmZzZXQ9IjAuNSIgc3RvcC1jb2xvcj0iIzIwMjEyMCIvPgogICAgICA8c3RvcCBvZmZzZXQ9IjAuNjAyIiBzdG9wLWNvbG9yPSIjMjAyMTIwIi8+CiAgICAgIDxzdG9wIG9mZnNldD0iMSIgc3RvcC1jb2xvcj0iIzZjNmM2YyIvPgogICAgPC9saW5lYXJHcmFkaWVudD4KICA8L2RlZnM+CiAgPHJlY3QgY2xhc3M9ImNscy0xIiB3aWR0aD0iMjQiIGhlaWdodD0iMTYiLz4KPC9zdmc+Cg==\"/>\n"
"            <feComposite result=\"composite\" operator=\"in\" in2=\"SourceGraphic\"/>\n"
"            <feBlend result=\"blend\" in2=\"SourceGraphic\"/>\n"
"        </filter>\n"
"        <filter id=\"logo-black-filter-5\" x=\"9\" y=\"3\" width=\"20\" height=\"14\" filterUnits=\"userSpaceOnUse\">\n"
"            <feImage preserveAspectRatio=\"none\" x=\"9\" y=\"3\" width=\"20\" height=\"14\" result=\"image\"\n"
"                     xlink:href=\"data:image/svg+xml;base64,PHN2ZyB4bWxucz0iaHR0cDovL3d3dy53My5vcmcvMjAwMC9zdmciIHhtbG5zOnhsaW5rPSJodHRwOi8vd3d3LnczLm9yZy8xOTk5L3hsaW5rIiB3aWR0aD0iMjAiIGhlaWdodD0iMTQiIHZpZXdCb3g9IjAgMCAyMCAxNCI+CiAgPGRlZnM+CiAgICA8c3R5bGU+CiAgICAgIC5jbHMtMSB7CiAgICAgICAgZmlsbDogdXJsKCNsaW5lYXItZ3JhZGllbnQpOwogICAgICB9CiAgICA8L3N0eWxlPgogICAgPGxpbmVhckdyYWRpZW50IGlkPSJsaW5lYXItZ3JhZGllbnQiIHgxPSI4Ljc2NiIgeTE9IjE0IiB4Mj0iMTEuMjM0IiBncmFkaWVudFVuaXRzPSJ1c2VyU3BhY2VPblVzZSI+CiAgICAgIDxzdG9wIG9mZnNldD0iMCIgc3RvcC1jb2xvcj0iIzIwMjEyMCIvPgogICAgICA8c3RvcCBvZmZzZXQ9IjAuMTAyIiBzdG9wLWNvbG9yPSIjMjAyMTIwIi8+CiAgICAgIDxzdG9wIG9mZnNldD0iMC41IiBzdG9wLWNvbG9yPSIjNmM2YzZjIi8+CiAgICAgIDxzdG9wIG9mZnNldD0iMC44OTgiIHN0b3AtY29sb3I9IiMyMDIxMjAiLz4KICAgICAgPHN0b3Agb2Zmc2V0PSIxIiBzdG9wLWNvbG9yPSIjMjAyMTIwIi8+CiAgICA8L2xpbmVhckdyYWRpZW50PgogIDwvZGVmcz4KICA8cmVjdCBjbGFzcz0iY2xzLTEiIHdpZHRoPSIyMCIgaGVpZ2h0PSIxNCIvPgo8L3N2Zz4K\"/>\n"
"            <feComposite result=\"composite\" operator=\"in\" in2=\"SourceGraphic\"/>\n"
"            <feBlend result=\"blend\" in2=\"SourceGraphic\"/>\n"
"        </filter>\n"
"    </defs>\n"
"    <path class=\"logo-black-cls-1\"\n"
"          d=\"M31,30L19,37,7,30V18h5V14H26v4h5V30Z\"/>\n"
"    <path class=\"logo-black-cls-2\"\n"
"          d=\"M29,28L19,34,9,28V20h5V17H24v3h5v8Z\"/>\n"
"    <path class=\"logo-black-cls-3\"\n"
"          d=\"M26,27l-7,4-7-4V22h4V19h6v3h4v5Z\"/>\n"
"    <path class=\"logo-black-cls-4\"\n"
"          d=\"M27.007,17V12.691C27.007,4.582,20.042,4,19,4c-0.88,0-9.006.5-9.006,8.691V17H7V13.092c0-7.719,5.394-12.1,12.013-12.1s11.994,4.344,11.994,12.1L31,17h-4Z\"/>\n"
"    <path class=\"logo-black-cls-5\"\n"
"          d=\"M26.99,17L27,13c0-8.246-7.021-8-8-8-0.826,0-8-.072-8,8l0.011,4H9V13.047C9,5.485,13.766,3,19,3c5.034,0,9.99,2.485,9.99,10.047l0,3.953h-2Z\"/>\n"
"</svg>";
}

std::string getTextLogo() {
    return "<svg xmlns=\"http://www.w3.org/2000/svg\" viewBox=\"0 0 48.418749 6.3500002\" fill=\"#2f313b\" height=\"24\" width=\"183\"><path d=\"M32.678 0c-.983 0-1.435.009-2.1.08v6.154h.78V3.773c.38.044.885.08 1.408.08 1.381 0 1.878-.41 1.878-1.926C34.644.42 34.148 0 32.678 0zM1.984.009C1.08.009.61.018 0 .081v6.153c.69.062 1.213.071 2.258.071 1.4 0 1.948-.338 1.948-1.605 0-.98-.31-1.56-1.222-1.641v-.036c.735-.07 1.036-.526 1.036-1.409C4.02.348 3.48.01 1.984.01zm16.379.036c-.15 0-.23.089-.23.232v.508c0 .16.08.232.23.232h.354c.16 0 .23-.072.23-.232V.277c0-.143-.07-.232-.23-.232zm-3.276.562V1.9l-.779.036v.552h.78v2.65c0 .757.38 1.176 1.107 1.176.212 0 .69-.035.973-.116l-.088-.58h-.655c-.425 0-.585-.16-.585-.58v-2.55h1.373v-.597H15.84V.607zM.761.677h1.187c.983 0 1.32.188 1.32 1.027 0 .829-.31 1.034-1.196 1.043H.762zm31.908 0c.885 0 1.186.26 1.186 1.25s-.3 1.24-1.186 1.248h-1.31V.687c.344-.009.796-.009 1.31-.009zM7.439 1.785c-.646 0-1.487.098-2.08.196l.07.562c.656-.063 1.4-.116 1.851-.116.682 0 .877.214.877.749v.384H6.359c-.752 0-1.195.392-1.195 1.07v.473c0 .784.522 1.212 1.293 1.212.788 0 1.443-.446 1.78-.793l.088.713h.593V3.175c0-1.052-.522-1.39-1.478-1.39zm4.258 0c-1.177-.018-1.682.187-1.682 1.195 0 .714.275 1.043.974 1.213l1.24.285c.416.098.682.178.682.606 0 .518-.301.607-1.266.607a19.015 19.015 0 0 1-1.488-.036l-.053.553c.735.116 1.381.125 1.691.125 1.249 0 1.842-.179 1.842-1.249 0-.74-.319-1.025-1-1.195l-1.258-.285c-.416-.098-.629-.17-.629-.624 0-.544.266-.562 1.063-.553.54 0 1.098.027 1.638.045l.062-.553a14.982 14.982 0 0 0-1.816-.134zm10.456 0c-1.479 0-2.027.624-2.027 2.283 0 1.668.548 2.283 2.027 2.283 1.488 0 2.028-.615 2.028-2.283 0-1.659-.54-2.283-2.028-2.283zm5.83 0c-.637 0-1.275.294-1.93.794L26 1.89h-.638v4.343h.753V3.113c.69-.428 1.151-.687 1.665-.687.443 0 .62.187.62.767v3.04h.752V2.98c0-.785-.407-1.195-1.169-1.195zm9.742 0c-.647 0-1.488.098-2.081.196l.07.562c.656-.063 1.4-.116 1.851-.116.682 0 .877.214.877.749v.384h-1.797c-.753 0-1.196.392-1.196 1.07v.473c0 .784.522 1.212 1.293 1.212.788 0 1.443-.446 1.78-.793l.088.713h.594V3.175c0-1.052-.523-1.39-1.48-1.39zm4.258 0c-1.178-.018-1.683.187-1.683 1.195 0 .714.274 1.043.974 1.213l1.24.285c.416.098.682.178.682.606 0 .518-.302.607-1.267.607a19.015 19.015 0 0 1-1.487-.036l-.053.553c.735.116 1.381.125 1.691.125 1.249 0 1.842-.179 1.842-1.249 0-.74-.319-1.025-1-1.195l-1.258-.285c-.417-.098-.629-.17-.629-.624 0-.544.266-.562 1.063-.553.54 0 1.098.027 1.638.045l.062-.553a14.974 14.974 0 0 0-1.815-.134zm4.496 0c-1.178-.018-1.682.187-1.682 1.195 0 .714.274 1.043.974 1.213l1.24.285c.416.098.682.178.682.606 0 .518-.302.607-1.267.607a19.016 19.016 0 0 1-1.487-.036l-.054.553c.735.116 1.382.125 1.692.125 1.248 0 1.842-.179 1.842-1.249 0-.74-.319-1.025-1-1.195l-1.258-.285c-.417-.098-.63-.17-.63-.624 0-.544.266-.562 1.063-.553.54 0 1.099.027 1.639.045l.062-.553a14.982 14.982 0 0 0-1.816-.134zm-28.311.107v4.343h.744V1.89zm3.985.535c.939 0 1.249.375 1.249 1.641s-.31 1.64-1.249 1.64c-.938 0-1.24-.374-1.24-1.64s.302-1.64 1.24-1.64zM.761 3.344h1.32c1 .018 1.337.268 1.337 1.223 0 .873-.319 1.07-1.284 1.07-.531 0-1.01 0-1.373-.01zm5.731.794h1.665v.874c-.496.446-1.125.66-1.55.651-.469 0-.673-.196-.673-.65v-.277c0-.366.142-.58.558-.598zm30.285 0h1.665v.874c-.496.446-1.125.66-1.55.651-.47 0-.673-.196-.673-.65v-.277c0-.366.142-.58.558-.598z\"/></svg>";
}

std::string getTriangle() {
    return "<svg xmlns=\"http://www.w3.org/2000/svg\" viewBox=\"0 0 120 35\" height=\"25\" fill=\"white\" width=\"100\"><defs><filter id=\"triangle\" color-interpolation-filters=\"sRGB\"><feFlood result=\"flood\" flood-color=\"#343846\" flood-opacity=\".15\"/><feComposite result=\"composite1\" operator=\"in\" in2=\"SourceGraphic\" in=\"flood\"/><feGaussianBlur result=\"blur\" stdDeviation=\"5\" in=\"composite1\"/><feOffset result=\"offset\" dy=\"2\"/><feComposite result=\"composite2\" in2=\"offset\" in=\"SourceGraphic\"/></filter></defs><path d=\"M34.86 12.5L10 0h100L85.14 12.5C71.468 19.375 60.154 25 60 25c-.154 0-11.468-5.625-25.14-12.5z\" filter=\"url(#triangle)\"/></svg>";
}

std::string getHeaderWithLogo() {
    return "<div class=\"header-container\">"
        "<div class=\"header\"> "
        "    <div class=\"logo\">" + getLogo() + "</div> "
        "    <div class=\"text-logo\">" + getTextLogo() + "</div> "
        "    <div class=\"right-part\"></div>"
        "    <div class=\"triangle\">" + getTriangle() + "</div>"
        "</div> "
    "</div>";
}

std::string generateStockContent(const std::string title, const std::string header, const std::string text) {
    return "<!DOCTYPE html>"
        "<html>"
        "<head>" + getStyleTag() +
        "<title>" + title + "</title>"
        "</head>"
        "<body>" + getHeaderWithLogo() +
        "<div class=\"content\">"
            "<h1>" + header + "</h1>"
            "<div class=\"msg\">" + text + "</h1>"
        "</div>"
        "</body>"
        "</html>";
}
