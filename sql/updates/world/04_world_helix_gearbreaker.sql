UPDATE `creature_template` SET `faction_A`= 16, `faction_H`= 16 WHERE `entry` IN (48940, 48939);
UPDATE `creature_template` SET `faction_A`= 14, `faction_H`= 14, `unit_flags`= 0, `scriptname`= 'npc_sticky_bomb' WHERE `entry`= 47314;
UPDATE `creature_template` SET `scriptname`= 'npc_helix_crew'  WHERE `entry`= 49136;
DELETE FROM `creature` WHERE `guid` = 782386;
DELETE FROM creature_addon WHERE guid = 782386;

REPLACE INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
-- Helix Gearbreaker
(47296, 0, 0, 'The mistress will pay me handsomely for your heads!', 14, 0, 100, 0, 0, 20849, 'Helix Ritzelbrecher'),
(47296, 1, 0, 'Bombs away!', 14, 0, 100, 0, 0, 20847, 'Helix Ritzelbrecher'),
(47296, 2, 0, 'Ready Oafie? Throw!', 14, 0, 100, 0, 0, 20848, 'Helix Ritzelbrecher'),
(47296, 3, 0, 'Helix attachs a bomb to $N\'s chest!', 41, 0, 100, 0, 0, 0, 'Helix Ritzelbrecher'),
(47296, 4, 0, 'I didn\'t need him! Not when I\'ve got YOU oafs!', 14, 0, 100, 0, 0, 20846, 'Helix - Phase 2'),
(47296, 5, 0, 'Only 10 copper!? You\'re not even worth killing!', 14, 0, 100, 0, 0, 20845, 'Helix - Slay'),
(47296, 6, 0, 'The scales... have... tipped...', 14, 0, 100, 0, 0, 20844, 'Helix - Slay'),
-- Helix Crew
(49136, 0, 0, 'Blowin\' em\' to bits, boss!', 12, 0, 100, 0, 0, 0, 'Helix Crew - Throw Bomb'),
-- Lumbering Oaf
(47297, 0, 0, 'No...NO!', 14, 0, 100, 0, 0, 20854, 'Lumbering Oaf - Charge 1'),
(47297, 1, 0, 'OAF SMASH!!', 14, 0, 100, 0, 0, 0, 'Lumbering Oaf - Charge 2'),
(47297, 2, 0, 'Me...not feel so good...', 14, 0, 100, 0, 0, 20855, 'Lumbering Oaf - Death');

REPLACE INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES

(88278, 'spell_dm_ride_oaf');

DELETE FROM conditions WHERE SourceEntry = 88295;

INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, SourceEntry, SourceId, ElseGroup, ConditionTypeOrReference, ConditionTarget, ConditionValue1, ConditionValue2, ConditionValue3, NegativeCondition, ErrorType, ScriptName, Comment) VALUES

(13, 1, 88295, 0, 0, 31, 0, 3, 45979, 0, 0, 0, '', 'Oaf Smash - Target Dummy');

-- Deletes creature General Purpose Bunny JMF (id: 45979, guid: 782679) in zone: 1581, area: 1581
DELETE FROM `creature` WHERE `guid` = 782679; DELETE FROM creature_addon WHERE guid = 782679;

-- Deletes creature General Purpose Bunny JMF (id: 45979, guid: 782680) in zone: 1581, area: 1581
DELETE FROM `creature` WHERE `guid` = 782680; DELETE FROM creature_addon WHERE guid = 782680;

-- Deletes creature Helix' Crew (id: 49138, guid: 782722) in zone: 1581, area: 1581
DELETE FROM `creature` WHERE `guid` = 782722; DELETE FROM creature_addon WHERE guid = 782722;

-- Deletes creature Helix' Crew (id: 49136, guid: 782708) in zone: 1581, area: 1581
DELETE FROM `creature` WHERE `guid` = 782708; DELETE FROM creature_addon WHERE guid = 782708;

-- Deletes creature Helix' Crew (id: 49139, guid: 782721) in zone: 1581, area: 1581
DELETE FROM `creature` WHERE `guid` = 782721; DELETE FROM creature_addon WHERE guid = 782721;

-- Deletes creature Helix' Crew (id: 49137, guid: 782709) in zone: 1581, area: 1581
DELETE FROM `creature` WHERE `guid` = 782709; DELETE FROM creature_addon WHERE guid = 782709;

-- Deletes creature Helix' Crew (id: 49136, guid: 782720) in zone: 1581, area: 1581
DELETE FROM `creature` WHERE `guid` = 782720; DELETE FROM creature_addon WHERE guid = 782720;

-- Deletes creature Helix' Crew (id: 49138, guid: 782707) in zone: 1581, area: 1581
DELETE FROM `creature` WHERE `guid` = 782707; DELETE FROM creature_addon WHERE guid = 782707;

-- Deletes creature Helix' Crew (id: 49139, guid: 782706) in zone: 1581, area: 1581
DELETE FROM `creature` WHERE `guid` = 782706; DELETE FROM creature_addon WHERE guid = 782706;

-- Deletes creature Helix' Crew (id: 49137, guid: 782719) in zone: 1581, area: 1581
DELETE FROM `creature` WHERE `guid` = 782719; DELETE FROM creature_addon WHERE guid = 782719;
