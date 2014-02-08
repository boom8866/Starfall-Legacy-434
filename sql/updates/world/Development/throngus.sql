
/*
14:43:32.107 -- aggro
14:43:38.846 -- mighty stomp
14:43:42.465 -- pick weapon #2
14:44:27.471 -- mighty stomp #2
*/


UPDATE `creature_template` SET `scriptname`= 'boss_forgemaster_throngus' WHERE `entry`= 40177;
UPDATE `creature_template` SET `scriptname`= 'npc_gb_cave_in' WHERE `entry`= 40228;

DELETE FROM `creature_text` WHERE `entry`= 40177;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
(40177, 0, 0, 'NO! Throngus get whipped again if he no finish', 14, 0, 100, 0, 0, 18943, 'Schmiedemeister Throngus'),
(40177, 1, 0, 'Throngus use your corpse on body. Somewhere...', 14, 0, 100, 0, 0, 18944, 'Schmiedemeister Throngus'),
(40177, 1, 1, 'You break easy!', 14, 0, 100, 0, 0, 18944, 'Schmiedemeister Throngus'),
(40177, 2, 0, '|TInterface\\Icons\\inv_shield_76.blp:20|t%s legt seinen |cFFFF0000Schild|r an und erhält |cFFFF0000|Hspell:74908|h''Persönliche Phalanx''|h|r!', 41, 0, 100, 0, 0, 0, 'Schmiedemeister Throngus to Schmiedemeister Throngus'),
(40177, 3, 0, 'You not get through defenses!', 14, 0, 100, 0, 0, 18947, 'Schmiedemeister Throngus to Schmiedemeister Throngus'),
(40177, 4, 0, '|TInterface\\Icons\\inv_mace_15.blp:20|t%s legt seinen |cFFFF0000Streitkolben|r an und ist |cFFFF0000|Hspell:75007|h''Beeinträchtigt''|h|r!', 41, 0, 100, 53, 0, 0, 'Schmiedemeister Throngus to Schmiedemeister Throngus'),
(40177, 5, 0, 'Oh, this is gonna HURT!', 14, 0, 100, 53, 0, 18949, 'Schmiedemeister Throngus to Schmiedemeister Throngus'),
(40177, 6, 0, '|TInterface\\Icons\\ability_dualwield.blp:20|t%s legt seine |cFFFF0000Schwerter|r an und erhält |cFFFF0000|Hspell:74981|h''Dualklingen''|h|r!', 41, 0, 100, 0, 0, 0, 'Schmiedemeister Throngus to Schmiedemeister Throngus'),
(40177, 7, 0, 'Throngus SLICE you up!', 14, 0, 100, 0, 0, 18948, 'Schmiedemeister Throngus to Schmiedemeister Throngus'),
(40177, 8, 0, '$N wurde aufgespießt!', 41, 0, 100, 0, 0, 0, 'Schmiedemeister Throngus'),
(40177, 9, 0, 'Death... Good choice. Not best choice maybe, but better than fail and live.', 14, 0, 100, 0, 0, 18946, 'Schmiedemeister Throngus');

REPLACE INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(100605, 'spell_fl_empower_sulfuras'),
