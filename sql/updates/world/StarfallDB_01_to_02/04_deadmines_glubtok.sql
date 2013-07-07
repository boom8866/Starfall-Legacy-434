/*
18:52:23.174 -- aggro
70889 -- notiz
18:52:41.348 -- blink 1: 18 seconds
18:52:54.608 -- blink 2: 13 seconds

18:53:06.261 -- teleport
18:53:10.083 -- ready ?
18:53:12.486
18:53:14.888 -- arkane macht cast

18:53:18.523
18:53:20.707 -- blossom targeting
18:53:23.109 -- fire blossom 
*/

-- Glubtok Encounter

UPDATE `creature_template` SET `scriptname`= 'boss_glubtok', `exp`= 3 WHERE `entry`= 47162;
UPDATE `creature_template` SET `scriptname`= 'npc_dm_firewall_rotator'  WHERE `entry`= 48974;
DELETE FROM conditions WHERE SourceEntry IN (88072, 88093, 88140);
INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, SourceEntry, SourceId, ElseGroup, ConditionTypeOrReference, ConditionTarget, ConditionValue1, ConditionValue2, ConditionValue3, NegativeCondition, ErrorType, ScriptName, Comment) VALUES
(13, 1, 88072, 0, 0, 31, 0, 3, 47162, 0, 0, 0, '', 'Glubtok - Firebeam Target Glubtok'),
(13, 1, 88093, 0, 0, 31, 0, 3, 47162, 0, 0, 0, '', 'Glubtok - Frostbeam Target Glubtok'),
(13, 1, 88140, 0, 0, 31, 0, 3, 47282, 0, 0, 0, '', 'Glubtok - Blossom Targeting'),
(13, 2, 88140, 0, 0, 31, 0, 3, 47284, 0, 0, 0, '', 'Glubtok - Blossom Targeting');

DELETE FROM `creature_text` WHERE `entry`= 47162;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
(47162, 0, 0, 'Glubtok zeigt Euch arkane Macht!', 14, 0, 100, 0, 0, 21151, 'Glubtok'),
(47162, 2, 0, 'Flammenfäuste!', 14, 0, 100, 0, 0, 21153, 'Glubtok'),
(47162, 1, 0, 'Frostfäuste!', 14, 0, 100, 0, 0, 21156, 'Glubtok'),
(47162, 3, 0, 'Glubtok bereit?', 14, 0, 100, 1, 0, 21154, 'Glubtok'),
(47162, 4, 0, 'Los geht''s!', 14, 0, 100, 15, 0, 21157, 'Glubtok'),
(47162, 5, 0, 'ARKANE MACHT!', 14, 0, 100, 15, 0, 21146, 'Glubtok'),
(47162, 6, 0, '|TInterface\\Icons\\spell_holy_innerfire.blp:20|t Glubtok erschafft eine sich bewegende |cFFFF0000|Hspell:91398|h''Feuerwand''|h|r!', 41, 0, 100, 0, 0, 0, 'Glubtok'),
(47162, 7, 0, 'ZU... VIEL... MACHT!!!', 14, 0, 100, 15, 0, 21145, 'Glubtok');

DELETE FROM `creature_template_addon` WHERE `entry` IN (48974, 48975, 49039, 49040, 48976, 49041, 49042);
