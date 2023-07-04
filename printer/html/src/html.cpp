#include "dig-logger/printer/html.hpp"

#include <dig-logger/printer/formatter.hpp>
#include <iomanip>

namespace DIG {
namespace Logger {
namespace Printer {

void Html::log(                                      //
    const Level level,                               //
    const std::string_view tag,                      //
    const std::optional<std::exception>& exception,  //
    const std::string_view message,                  //
    const std::source_location& source               //
) {
  std::lock_guard lock(mutex);

  output << "<tr class=\"" << Formatter::level_long(level) << "\">";
  output << "<td class=\"time\">";
  Formatter::current_date(output);
  output << "</td>";
  output << "<td class=\"line\">" << source.line() << "</td>";
  output << "<td class=\"file\">" << source.file_name() << "</td>";
  output << "<td class=\"tag\">" << tag << "</td>";
  output << "<td class=\"message\">";
  for (auto& c : message) {
    if (c == '\n')
      output << "<br/>";
    else [[likely]]
      output << c;
  }
  if (exception.has_value()) {
    if (!message.empty()) {
      output << "<br/>Exception:";
    }
    output << exception->what();
  }
  output << "</td></tr>";
}

void Html::header() {
  auto l_none = Formatter::level_long(Level::NONE);
  auto l_verbose = Formatter::level_long(Level::VERBOSE);
  auto l_debug = Formatter::level_long(Level::DEBUG);
  auto l_information = Formatter::level_long(Level::INFORMATION);
  auto l_warning = Formatter::level_long(Level::WARNING);
  auto l_error = Formatter::level_long(Level::ERROR);
  auto l_assert = Formatter::level_long(Level::ASSERT);

  output << "<!DOCTYPE html><head><title>Log</title><style>"
            "body {background:#181818;color:#ccc;font-family:monospace;font-size:10pt;}"
            "table {width:100%;border-top:1px solid #333;border-left:1px solid #333;cellpadding:0;cellspacing:0;}"
            "tr:hover {background:#222;}"
            "td {padding:1pt 2pt 1pt 1pt;color:#aaa;border-bottom:1px solid #666;}"
            "th {color:#767676;border-bottom:1px solid #333;text-align:center;}"
            ".time {width:80pt;text-align:right;}"
            ".file {width:200px;}"
            ".line {text-align:right;width:50px;}";
            ".tag {width:80pt;}";

  output << ".level_" << l_none << " .message:before {content:\"None: \";color:#ccc;}";
  output << ".level_" << l_none << " .td {color:#ccc;}";

  output << ".level_" << l_verbose << " .message:before {content:\"None: \";color:#767676;}";
  output << ".level_" << l_verbose << " .td {color:#767676;}";

  output << ".level_" << l_debug << " .message:before {content:\"None: \";color:#ccc;}";
  output << ".level_" << l_debug << " .td {color:#ccc;}";

  output << ".level_" << l_information << " .message:before {content:\"None: \";color:#61d6d6;}";
  output << ".level_" << l_information << " .td {color:#61d6d6;}";

  output << ".level_" << l_warning << " .message:before {content:\"None: \";color:#c19c00;}";
  output << ".level_" << l_warning << " .td {color:#c19c00;}";

  output << ".level_" << l_error << " .message:before {content:\"None: \";color:#c50f1f;}";
  output << ".level_" << l_error << " .td {color:#c50f1f;}";

  output << ".level_" << l_assert << " .message:before {content:\"None: \";color:#b4009e;}";
  output << ".level_" << l_assert << " .td {color:#b4009e;}";

  output << "</style><body><table cellpadding=0 cellspacing=0><tr>"
            "<th class='time'>time</th>"
            "<th class='line'>line</th>"
            "<th class='file'>file</th>"
            "<th class='tag'>tag</th>"
            "<th class='message'>message</th></tr>";

  log(Level::VERBOSE, "Logger", std::optional<std::exception>(), "Init", std::source_location::current());
}

void Html::footer() {
  log(Level::VERBOSE, "Logger", std::optional<std::exception>(), "Finish", std::source_location::current());
  output << "</table></body></html>";
}

}  // namespace Printer
}  // namespace Logger
}  // namespace DIG