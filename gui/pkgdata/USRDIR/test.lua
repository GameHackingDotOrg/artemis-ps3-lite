--[[
    Arguments
]]
inf_health_opts = {
    { "Quarter", 12.5 },
    { "Half", 25 }
}

--[[
    Codes
]]
function set_health(health)

    writeFloat(0x010D7250, health)

end

--[[
    Definitions
]]
function __define(codelist)
    table.insert(codelist, {
        game = "Ratchet: Deadlocked",
        vers = "01.00",
        name = "Infinite Health",
        func = "set_health",
        desc = "Never die again!",
        args = {
            { options = inf_health_opts, multiselect = false }
        }
    })
end


foo = {}
__define(foo)

for index, data in ipairs(foo) do
    print (index)

    for key, value in pairs(data) do

        if key == "args" then
            for aIndex, aValue in ipairs(value) do
                for optionIndex, optionValue in ipairs(aValue) do
                    print('\t', key, aIndex, '\t', optionValue[1], optionValue[2]);
                end
            end
        else
            print('\t', key, value)
        end

        
    end
end
