
/*
21:56:38.186 -- aggro

21:56:45.206 -- first call lightnin

21:56:56.048 -- 2nd static disruption
21:57:08.107 -- 3rd static disruption

21:56:46.423 -- first gust of the wind
21:57:10.525 -- 2nd gust of the wind

21:57:00.884 -- 2nd ? call lightning
21:57:09.324 -- 3rd call lightning
21:57:17.763 -- next call lightning

21:56:48.435 -- soaring
21:56:51.633 -- cry and swoop

21:57:24.565 -- overload primer
21:57:25.002 -- electrical storm go


22:01:37.443 -- next primer
*/

UPDATE `creature_template` SET `scriptname`= 'boss_akilzon' WHERE `entry`= 23574;
UPDATE `creature_template` SET `InhabitType`= 4, `VehicleId`= 1612, `minlevel`= 85, `maxlevel`= 85, `exp`= 3, `faction_A`= 1890, `faction_H`= 1890,  `scriptname`= 'npc_amani_kidnapper' WHERE `entry`= 52638;
UPDATE `creature_template` SET `scriptname`= 'npc_soaring_eagle', `InhabitType`= 4, `exp`= 3 WHERE `entry`= 24858;

DELETE FROM `creature_text` WHERE `entry`= 23574;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
(23574, 0, 0, 'Ich bin der Jäger! Ihr seid die Beute...', 14, 0, 100, 0, 0, 12013, 'Akil''zon'),
(23574, 1, 0, 'Flasche!', 14, 0, 100, 0, 0, 12017, 'Akil''zon'),
(23574, 2, 0, 'Ein Gewitter zieht auf!', 41, 0, 100, 0, 0, 12196, 'Akil''zon'),
(23574, 3, 0, 'Labt euch, meine Brüder!', 14, 0, 100, 0, 0, 12014, 'Akil''zon to Akil''zon'),
(23574, 4, 0, 'Ihr könnt... meinen Geist... nicht töten!', 14, 0, 100, 0, 0, 12019, 'Akil''zon');

REPLACE INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES

(98869, 'spell_grab_passenger'),
(43648, 'spell_electrical_storm');
