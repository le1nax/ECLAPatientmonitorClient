// #pragma once
// #include "Constants.h"


// // Define the regular expressions
// const std::string ID_LINE_REGEX = "^\\s*(?<name>CAN_ID_\\w+)\\s*=\\s*0x(?<id>[0-9a-fA-F]+),?\\s*\\/\\/(?<description>[^\\|\\t]+)?\\s*(\\|\\s*(?<factor>\\d((\\.|\\,)\\d*)?)?\\s*(?<unit>[^\\|]*[^\\s\\|])?\\s*(\\|\\s*(?<caninterval>\\d+)?\\s*(?<sdinterval>\\d+)?\\s*(?<canthreshold>\\d+((\\.|\\,)\\d+)?)?\\s*(?<sdthreshold>\\d+((\\.|\\,)\\d+)?)?)?\\s*(\\|\\s*(?<min>\\d+)?\\s*(?<max>\\d+)?\\s*)?)?\\s*$";

    
// // specifies the format of a group definition line (if a count is defined, there must be a shifter define as well, even if the count is 1).
// // sample: "	// idGroup("Florian's Testarea", 5, CAN_TESTAREA_SHIFT, ALARM)"
// const std::string GROUP_LINE_REGEX = "^\\s*//\\s*idGroup\\(((?<none>none)|(\"(?<name>[^\"]+)\"(\\,\\s?(?<count>\\d{1,4})\\,\\s?(?<shifterDefine>\\w+))?(?<alarm>\\,\\s?ALARM)?))\\)\\s*$";

// // specifies the format of a numeric define, i.e. a define with a hex or a decimal number as value.
// // sample: "#define MY_DEFINE   0x123ABC"
// const std::string NUMERIC_DEFINE_REGEX = "^#define[ \t]+(?<name>\\w+)[ \t]+((0x(?<hexValue>[0-9a-fA-F]+))|(?<decValue>\\d+))[ \t]?(\\/\\/[^\\r\\n]*)?$";

// // specifies the format of the svn revision which is inserted by the svn revision property.
// // sample: "$Rev: 1868 $"
// const std::string REVISION_REGEX = "\\$Rev: (?<revision>\\d+) ?\\$";

// // specifies the begin of the enum which defines the CAN ids.
// const std::string ENUM_BEGIN_REGEX = "^\\s*enum\\s*can_id\\s*\\{(\\s*//.*)?$";

// // specifies the end of the enum.
// const std::string ENUM_END_REGEX = "^\\s*\\}\\s*;(\\s*//.*)$";

// // Define the constants
// const short DEFAULT_SHIFTER = 12;