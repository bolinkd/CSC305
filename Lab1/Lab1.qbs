import qbs

CppApplication {
    type: "application" // To suppress bundle generation on Mac
    consoleApplication: true
    files: [
        "linkedlistnode.cpp",
        "linkedlistnode.h",
        "main.cpp",
        "rectangle.cpp",
        "rectangle.h",
        "shape.cpp",
        "shape.h",
    ]

    Group {     // Properties for the produced executable
        fileTagsFilter: product.type
        qbs.install: true
    }
}

