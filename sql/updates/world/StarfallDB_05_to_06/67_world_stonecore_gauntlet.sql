/*
09:22:43.714 -- millhouse aggro

09:22:43.714 -- millhouse shadow bolt cast: 92641
09:22:44.853 -- new shadowbolt cast

09:23:12.902 -- flee + say # 1 
09:24:20.138 -- fleed #2

09:25:19.871 -- impending doom start

09:25:22.492 --  corborus charge
09:25:23.178 -- knockback
*/

UPDATE `instance_template` SET `script`= 'instance_the_stonecore' WHERE `map`= 725;

UPDATE `creature_template` SET `scriptname`= 'boss_corborus' WHERE `entry`= 43438;
DELETE FROM `creature_template_addon` WHERE `entry`= 43438;

UPDATE `creature_template` SET `minlevel`= 83, `maxlevel`= 83, `scriptname`= 'npc_tsc_millhouse_manastorm' WHERE `entry`= 43391;
REPLACE INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
(43391, 0, 0, 'Follow me if you dare!', 14, 0, 100, 0, 0, 21783, 'Millhouse Manastorm 1 - Flee 1'),
(43391, 0, 1, 'Prison taught me one very important lesson, well, two if you count how to hold your soap, but yes! SURVIVAL!', 14, 0, 100, 0, 0, 21789, 'Millhouse Manastorm 1 - Flee 2'),
(43391, 1, 0, 'Ah-ha! I\'ve got you right where I want you!', 14, 0, 100, 0, 0, 21787, 'Millhouse Manastorm 1 - Inpending Doooooom! 1'),
(43391, 2, 0, 'Now... witness the full power of Millhouse Manastorm!', 14, 0, 100, 0, 0, 21788, 'Millhouse Manastorm 1 - Inpending Doooooom! 2');

DELETE FROM `areatrigger_scripts` WHERE `entry`= 6076;

INSERT INTO `areatrigger_scripts` (`entry`, `ScriptName`) VALUES
(6076, 'at_tsc_corborus_intro');
