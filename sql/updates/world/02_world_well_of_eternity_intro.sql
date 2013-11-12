/*

17:44:13.972 -- intro 1
17:44:20.165 -- intro 2
17:44:23.722 -- intro 3
 17:44:28.402

17:44:19 -- salute

17:44:20.368
17:44:30.851
*/

UPDATE `instance_template` SET `script`= 'instance_well_of_eternity'  WHERE `map`= 939;

UPDATE `creature_template` SET `scriptname`= 'boss_perotharn' WHERE `entry`= 55085;
UPDATE `creature_template` SET `scriptname`= 'npc_legion_demon_intro' WHERE `entry`= 55503;

DELETE FROM `areatrigger_scripts` WHERE entry = 7029;
INSERT INTO `areatrigger_scripts` (`entry`, `ScriptName`) VALUES
(7029, 'at_woe_intro');

REPLACE INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
(55085, 1, 0, 'Er ist nah und verbirgt sich in den Schatten... Ich kann es spüren.', 12, 0, 100, 0, 0, 26118, 'Peroth\'arn'),
(55085, 2, 0, 'Du da, Teufelswache. Schütze diesen Bereich.', 12, 0, 100, 0, 0, 26120, 'Peroth\'arn'),
(55085, 3, 0, 'Ihr anderen sichert den Innenhof.', 12, 0, 100, 0, 0, 26121, 'Peroth\'arn');
