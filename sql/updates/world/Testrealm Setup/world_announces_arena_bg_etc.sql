DELETE FROM `trinity_string` WHERE `entry` IN
(11000, 4, 712, 717, 718, 7525, 719, 787, 6615, 2019,
2000, 2022, 2025, 2018, 2003, 2001, 2002, 2004, 2020);
INSERT INTO `trinity_string` (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`) VALUES
(11000, '|cffffffff[|cffff0000AutoMsg|cffffffff]: |cFFFFFF00%s|r', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
(4, '|cffff0000[Event]: %s|r', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
(712, '|cffff0000[BG Queue]:|r *%s* Lv [%u-%u] Alliance: %u/%u - Horde: %u/%u|r', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
(717, '|cffff0000[Battleground]:|r %s [Liv %u-%u] Started!|r', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
(718, '|cffff0000[Arena]|r - |cffffffff*|r|cFFFFA500Rated|r|cffffffff*|r:|r Match (|cffffffff%uv%u|r) Available!|r', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
(7525, '|cffff0000[Arena]|r - |cffffffff*|r|cff00ff00Skirmish|r|cffffffff*|r:|r Match (|cffffffff%uv%u|r) Available!|r', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
(719, '|cffff0000[Arena Announcer]:|r %s  Leave : %ux%u : %u|r', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
(787, '|cffff0000 <SoC Staff> |cffffffff[%s]:|cffffff00 %s|r', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
(6615, '|cffff0000 <GM> |cffffffff[%s]:|cffffff00 %s|r', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
(2019, '|cff00ff00Last Modified|r:|cff00ccff %s ago|r ', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
(2000, '|cff00ff00New ticket from|r|cffff00ff %s.|r |cff00ff00Ticket entry:|r|cffff00ff %d.|r', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
(2022, '|cff00ff00Message|r: [%s]|r', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
(2025, '|cff00ff00Created by|r:|cff00ccff %s ago|r ', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
(2018, '|cff00ff00Created by|r:|cff00ccff %s|r ', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
(2003, '|cff00ff00Closed by|r:|cff00ccff %s|r ', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
(2001, '|cff00ff00Character|r|cffff00ff %s |r|cff00ff00edited his/her ticket:|r|cffff00ff %d.|r', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
(2002, '|cff00ff00Character|r|cffff00ff %s |r|cff00ff00abandoned ticket entry:|r|cffff00ff %d.|r', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
(2004, '|cff00ff00Deleted by|r:|cff00ccff %s|r ', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
(2020, '|cff00ff00Assigned to|r:|cff00ccff %s|r ', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);