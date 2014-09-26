
REPLACE INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
(49427, 0, 0, 'I found this fascinating specimen in the lava underneath this very room. Magmaw should provide an adequate challenge for your pathetic little band.', 14, 0, 100, 0, 0, 23367, 'Nefarian - Magmaw Intro 1'),
(49427, 1, 0, 'On second thought, what fun is an \"adequate\" challenge?', 14, 0, 100, 0, 0, 23369, 'Nefarian - Magmaw Intro 2'),
(49427, 2, 0, 'Finally someone to deal with that unsightly pest! You have my thanks, \"heroes.\"', 14, 0, 100, 0, 0, 20085, 'Nefarian - Magmaw Death'),
(41570, 0, 0, '%s begins to erupt, spewing Lava Parasites onto the ground!', 41, 0, 100, 0, 0, 0, 'Magmaul to Magmaul'),
(41570, 1, 0, '%s slumps forward, exposing is pincers!', 41, 0, 100, 0, 0, 0, 'Magmaul'),
(41570, 2, 0, '%s becomes impaled on the spike exposing his head!', 41, 0, 100, 0, 0, 8717, 'Magmaul'),
(41570, 3, 0, '%s breaks free from its bindings!', 41, 0, 100, 0, 0, 0, 'Magmaul'),
(41570, 4, 0, 'You are close enough to reach Magmaw\'s head!', 42, 0, 100, 0, 0, 8717, 'Magmaul');

UPDATE `creature_template` SET `scriptname`= 'boss_magmaw' WHERE `entry`= 41570; -- Magmaw
UPDATE `creature_template` SET `scriptname`= 'npc_exposed_head_of_magmaw', `unit_flags`= 33554496 WHERE `entry`= 42347; -- Exposed Head of Magmaw
UPDATE `creature_template` SET `scriptname`= 'npc_exposed_head_of_magmaw_tank', `unit_flags`= 0, `rank`= 3, `type_flags`= 4 WHERE `entry`= 48270; -- Exposed Head of Magmaw Tank
UPDATE `creature_template` SET `modelid1`= 11686, `modelid2`= 0, `modelid3`= 0, `faction_A`= 1375, `faction_H`= 1375, `unit_flags`= 33554496, `unit_class`= 4, `scriptname`= 'npc_bwd_magmaws_pincer' WHERE `entry` IN (41620, 41789); -- Pincer
UPDATE `creature_template` SET `scriptname`= 'npc_bwd_pillar_of_flame', `modelid1`= 1126, `modelid2`= 16925, `unit_flags`= 33587264, `minlevel`= 85, `maxlevel`= 85, `faction_A`= 14, `faction_H`= 14, `flags_extra`= 131 WHERE `entry`= 41843; -- Pillar of Flame
UPDATE `creature_template` SET `scriptname`= 'npc_bwd_lava_parasite', `minlevel`= 85, `maxlevel`= 85, `exp`= 3, `faction_A`= 14, `faction_H`= 14  WHERE `entry` IN (41806, 42321); -- Lava Parasites
UPDATE `creature_template` SET `minlevel`= 85, `maxlevel`= 85, `faction_A`= 190, `faction_H`= 190,  `modelid1`= 1126, `modelid2`= 16925, `unit_flags`= 33587264, `flags_extra`= 131 WHERE `entry`= 47196; -- Room Stalker (Crash Visual)
UPDATE `creature_template` SET `scriptname`= 'npc_bwd_spike_dummy', `unit_flags`= 33554496 WHERE `entry`= 41767;

UPDATE `creature_template` SET `spell1`= 77917 WHERE `entry`= 41620; -- Pincer Vehicle 1
UPDATE `creature_template` SET `spell1`= 77941 WHERE `entry`= 41789; -- Pincer Vehicle 2

DELETE FROM `creature` WHERE `id` IN (47196, 47330);
DELETE FROM `creature_addon` WHERE `guid` NOT IN (SELECT `guid` FROM `creature`);
UPDATE `creature` SET `phaseMask`= 1, `spawnMask`= 15 WHERE `id` IN (49427, 41570);

REPLACE INTO `creature_template_addon` (`entry`, `Auras`) VALUES
(48270, '79011 95478'),
(42347, '79011');

DELETE FROM `vehicle_template_accessory` WHERE `entry` IN (41570, 42347);
INSERT INTO `vehicle_template_accessory` (`entry`, `accessory_entry`, `seat_id`, `minion`, `description`, `summontype`, `summontimer`) VALUES
(41570, 41620, 0, 1, 'Magmaw - Pincer 1', 8, 0),
(41570, 41789, 1, 1, 'Magmaw - Pincer 2', 8, 0),
(41570, 42347, 3, 1, 'Magmaw - Exposed Head of Magmaw', 8, 0),
(41570, 48270, 4, 1, 'Magmaw - Exposed Head of Magmaw 2', 8, 0);

DELETE FROM `npc_spellclick_spells` WHERE `npc_entry` IN (41570, 41789, 42347, 41620);
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`) VALUES
(41570, 77901, 1),
(41789, 46598, 0),
(42347, 46598, 0),
(41620, 46598, 0);

REPLACE INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(77998, 'spell_bwd_pillar_of_flame_aoe'),
(77901, 'spell_bwd_ride_vehicle'),
(78643, 'spell_bwd_eject_passengers');

DELETE FROM `conditions` WHERE `SourceEntry` IN (78017, 78010, 78360, 77917, 77941, 77929, 77940, 78643);
INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, SourceEntry, SourceId, ElseGroup, ConditionTypeOrReference, ConditionTarget, ConditionValue1, ConditionValue2, ConditionValue3, NegativeCondition, ErrorType, ScriptName, Comment) VALUES
(13, 7, 78017, 0, 0, 31, 0, 3, 41570, 0, 0, 0, '', 'Pillar of Flame Dummy - Target Magmaw'),
(13, 7, 78010, 0, 0, 31, 0, 3, 41843, 0, 0, 0, '', 'Pillar of Flame Missile - Target Pillar of Flame trigger'),
(13, 7, 78360, 0, 0, 31, 0, 3, 41570, 0, 0, 0, '', 'Mangle - Target Magmaw'),
(13, 7, 77917, 0, 0, 31, 0, 3, 41767, 0, 0, 0, '', 'Launch Hook - Target Spike Dummy'),
(13, 7, 77941, 0, 0, 31, 0, 3, 41767, 0, 0, 0, '', 'Launch Hook - Target Spike Dummy'),
(13, 7, 77940, 0, 0, 31, 0, 3, 41570, 0, 0, 0, '', 'Chain Visual - Target Magmaw'),
(13, 7, 77929, 0, 0, 31, 0, 3, 41570, 0, 0, 0, '', 'Chain Visual - Target Magmaw'),
(13, 7, 78643, 0, 0, 31, 0, 3, 41789, 0, 0, 0, '', 'Eject Passengers - Target Pincer L'),
(13, 7, 78643, 1, 0, 31, 0, 3, 41620, 0, 0, 0, '', 'Eject Passengers - Target Pincer R');
