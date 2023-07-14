import("core.base.option")
local options =
{
    {'t', "target", "kv", nil, "Test target"}
}

function main(argv)
    local args = option.parse(argv, options, "Run tests and report to Appveyor")
    local target = args.target
    if target == nil then
        raise "Requires target to test"
    end
    local start = os.mclock()
    local build = exec(format("xmake b %s", target))
    if not build then
        local time = os.mclock() - start
        exec(format("appveyor AddTest \"%s\" -Framework \"Custom\" -Filename \"%s\" -Duration %d -Outcome Failed -ErrorMessage \"Failed to build\"", target, target, time))
        return 0
    end
    local test = exec(format("xmake r %s", target))
    if not test then
        local time = os.mclock() - start
        exec(format("appveyor AddTest \"%s\" -Framework \"Custom\" -Filename \"%s\" -Duration %d -Outcome Failed -ErrorMessage \"Error running test\"", target, target, time))
        return 0
    end
    local time = os.mclock() - start
    exec(format("appveyor AddTest \"%s\" -Framework \"Custom\" -Filename \"%s\" -Duration %d -Outcome Passed", target, target, time))
end

function exec(command)
    return try { function()
         os.exec(command)
         return true
    end} or false
end