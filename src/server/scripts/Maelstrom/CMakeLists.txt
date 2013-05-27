file(GLOB_RECURSE scripts_TheStonecore Maelstrom/TheStonecore/*.cpp Maelstrom/TheStonecore/*.h)
file(GLOB_RECURSE scripts_Zones Maelstrom/*.cpp Maelstrom/*.h)

source_group(Maelstrom\\TheStonecore FILES ${scripts_TheStonecore})
source_group(Maelstrom\\Zones FILES ${scripts_Zones})

set(scripts_STAT_SRCS
  ${scripts_STAT_SRCS}
  ${scripts_TheStonecore}
  ${scripts_Zones}
)

message("  -> Prepared: The Maelstrom")
