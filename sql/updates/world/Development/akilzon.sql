
/*
22:00:49.847 -- aggro

22:00:55.681 -- static disruption # 1
22:01:07.756 -- static disruption # 2

22:00:56.882 -- call lightning #1
22:01:05.338 -- call lightning #2

22:01:37.443 -- primer #1

[0] Waypoint: X: 360.2517 Y: 1422.922 Z: 79.72605
[1] Waypoint: X: 373.9844 Y: 1431.182 Z: 79.85269
[2] Waypoint: X: 395.0295 Y: 1425.84 Z: 79.52386
[3] Waypoint: X: 399.2049 Y: 1398.422 Z: 79.31239
[4] Waypoint: X: 390.6059 Y: 1390.115 Z: 79.76962
[5] Waypoint: X: 372.6267 Y: 1383.906 Z: 79.27089
[6] Waypoint: X: 354.8368 Y: 1397.519 Z: 79.28339
[7] Waypoint: X: 353.4097 Y: 1414.561 Z: 79.52943

kidnapper path
*/

UPDATE `creature_template` SET `scriptname`= 'boss_akilzon' WHERE `entry`= 23574;
UPDATE `creature_template` SET `InhabitType`= 4, `VehicleId`= 1612, `minlevel`= 85, `maxlevel`= 85, `exp`= 3, `faction_A`= 1890, `faction_H`= 1890,  `scriptname`= 'npc_amani_kidnapper' WHERE `entry`= 52638;
UPDATE `creature_template` SET `scriptname`= 'npc_soaring_eagle', `InhabitType`= 4, `exp`= 3 WHERE `entry`= 24858;

DELETE FROM `creature_text` WHERE `entry`= 23574;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
(23574, 0, 0, 'I be da predator! You da prey...', 14, 0, 100, 0, 0, 12013, 'Akil''zon - Aggro'),
(23574, 1, 0, 'Ya got nothin\'!', 14, 0, 100, 0, 0, 12017, 'Akil''zon - Slay 1'),
(23574, 2, 0, 'An electrical storm appears!', 41, 0, 100, 0, 0, 12196, 'Akil''zon - Announce Storm'),
(23574, 3, 0, 'Feed, me bruddahs!', 14, 0, 100, 0, 0, 12014, 'Akil''zon to Akil''zon - Summon Eagles'),
(23574, 4, 0, 'You can\'t... kill... me spirit!', 14, 0, 100, 0, 0, 12019, 'Akil''zon - Death');

REPLACE INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES

(98869, 'spell_grab_passenger'),
(43648, 'spell_electrical_storm'),
(97300, 'spell_electrical_storm_damage'),
(44735, 'spell_electrical_overload_primer');
