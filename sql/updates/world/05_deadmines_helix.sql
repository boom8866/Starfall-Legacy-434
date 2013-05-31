
-- DB Stuff for Helix encounter
UPDATE `creature_template` SET `scriptname`= 'boss_helix_gearbreaker' WHERE `entry`= 47296;
UPDATE `creature_template` SET `scriptname`= 'npc_lumbering_oaf' WHERE `entry`= 47297;
UPDATE `creature_template` SET `scriptname`= 'npc_helix_crew' WHERE `entry`= 49139;
UPDATE `creature_template` SET `scriptname`= 'npc_sticky_bomb', `minlevel`= 85, `maxlevel`= 85 WHERE `entry`= 47314;

-- manually spawn helix
DELETE FROM `creature` WHERE `guid` = 785575;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `curhealth`, `curmana`) VALUES
(785575, 47296, 36, 4294967295, 1, -305.148102, -516.838989, 53.218662, 0.151292, 300, 100000000, 34797);
DELETE FROM `creature_text` WHERE `entry` IN (47296, 49136, 47297);
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
(47296, 0, 0, 'Die Herrin entlohnt mich gut für Eure Köpfe!', 14, 0, 100, 0, 0, 20849, 'Helix Ritzelbrecher'),
(47296, 1, 0, 'Feuer frei!', 14, 0, 100, 0, 0, 20847, 'Helix Ritzelbrecher'),
(47296, 1, 1, 'Fertig, Trampel? Wirf!', 14, 0, 100, 0, 0, 20848, 'Helix Ritzelbrecher'),
(47296, 2, 0, 'Helix befestigt eine Bombe an der Brust von $N!', 41, 0, 100, 0, 0, 0, 'Helix Ritzelbrecher'),
(47296, 3, 0, 'Ich brauch ihn nicht, ich hab ja EUCH Trampel!', 14, 0, 100, 0, 0, 20846, 'Helix Ritzelbrecher to Trampel'),
(49136, 0, 0, 'Sie werden in Stücke geschossen, Boss!', 12, 0, 100, 0, 0, 0, 'Helix'' Besatzungsmitglied'),
(47297, 0, 0, 'Nein…NEIN!', 14, 0, 100, 0, 0, 20854, 'Trampel to Helix Ritzelbrecher'),
(47297, 1, 0, 'TRAMPEL ZERQUETSCHT!', 14, 0, 100, 0, 0, 0, 'Trampel to Helix Ritzelbrecher');

DELETE FROM `spell_script_names` WHERE `spell_id` IN (88352);
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(88352, 'spell_dm_chest_bomb');
