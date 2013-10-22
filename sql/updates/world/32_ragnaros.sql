
-- Set Spawnmask for 10 Player and 10 Player HC
UPDATE `creature` SET `spawnMask`= 5 WHERE `map`= 720;
UPDATE `gameobject` SET `spawnMask`= 5 WHERE `map`= 720;

-- Cleanup unneeded spawns
DELETE FROM `creature` WHERE `id` IN (53086, 53485, 53140, 53231, 52409, 53266, 53393, 53420, 53393, 53872, 53875, 53876);

-- Add trigger flags to trigger Npc's
UPDATE `creature_template` SET `flags_extra`= 130 WHERE `entry` IN (53268, 53266, 53363, 53268, 53420, 53393, 53485, 53473, 53186, 54074, 53953, 54293);

-- Scriptname for Areatrigger Script
DELETE FROM `areatrigger_scripts` WHERE entry = 6845;
INSERT INTO `areatrigger_scripts` (`entry`, `ScriptName`) VALUES
(6845, 'at_sulfuron_keep');

-- Template Updates
UPDATE `creature_template` SET `baseattacktime`= 2000, `difficulty_entry_1`= 53797, `difficulty_entry_2`= 53798, `difficulty_entry_3`= 53799, `scriptname`= 'boss_ragnaros_cata' WHERE `entry`= 52409;
UPDATE `creature_template` SET `scriptname`= 'npc_fl_archdruids' WHERE `entry` IN (53872, 53875, 53876);
UPDATE `creature_template` SET `exp`= 3, `minlevel`= 88, `maxlevel`= 88, `faction_A`= 2234, `faction_H`= 2234 WHERE `entry` IN (53797, 53798, 53799);
UPDATE `creature_template` SET `scriptname`= 'npc_fl_magma_trap' WHERE `entry`= 53086;
UPDATE `creature_template` SET `InhabitType`= 4, `scriptname`= 'npc_fl_lava_wave' WHERE `entry`= 53363;
UPDATE `creature_template` SET `InhabitType`= 4 WHERE `entry`= 53186;
UPDATE `creature_template` SET `scriptname`= 'npc_fl_sulfuras_smash' WHERE `entry`= 53268;
UPDATE `creature_template` SET `scriptname`= 'npc_fl_sulfuras_hammer' WHERE `entry`= 53420;
UPDATE `creature_template` SET `difficulty_entry_1`= 53800, `difficulty_entry_2`= 53801, `difficulty_entry_3`= 53802, `scriptname`= 'npc_fl_son_of_flame' WHERE `entry`= 53140;
UPDATE `creature_template` SET `speed_walk`= 1, `speed_run`= 1.71429 WHERE `entry`= 53801;
UPDATE `creature_template` SET `exp`= 3, `minlevel`= 87, `maxlevel`= 87, `faction_A`= 16, `faction_H`= 16 WHERE `entry` IN (53801, 53811, 53817, 53814);
UPDATE `creature_template` SET `scriptname`= 'npc_fl_engulfing_flame' WHERE `entry`= 53485;
UPDATE `creature_template` SET `mechanic_immune_mask`= 617299839, `InhabitType`= 4 WHERE `entry` IN (52409, 53797, 53798);
UPDATE `creature_template` SET `difficulty_entry_1`= 53810, `difficulty_entry_2`= 53811, `difficulty_entry_3`= 53812, `minlevel`= 87, `maxlevel`= 87, `exp`= 3, `faction_A`= 16, `faction_H`= 16, `scriptname`= 'npc_fl_molten_elemental' WHERE `entry`= 53189;
UPDATE `creature_template` SET `difficulty_entry_1`= 53816, `difficulty_entry_2`= 53817, `difficulty_entry_3`= 53818, `scriptname`= 'npc_fl_lava_scion' WHERE `entry`= 53231;
UPDATE `creature_template` SET `faction_A`= 16, `faction_H`= 16, `scriptname`= 'npc_fl_blazing_heat' WHERE `entry`= 53473;
UPDATE `creature_template` SET `difficulty_entry_1`= 53813, `difficulty_entry_2`= 53814, `difficulty_entry_3`= 53815, `faction_A`= 16, `faction_H`= 16, `minlevel`= 87, `maxlevel`= 87, `exp`= 3, `scriptname`= 'npc_fl_living_meteor' WHERE `entry` IN (53500, 53813, 53814, 53815);
UPDATE `creature_template` SET `minlevel`= 85, `maxlevel`= 85, `flags_extra`= 130, `scriptname`= 'npc_fl_dreadflame' WHERE `entry`= 54203;
UPDATE `creature_template` SET `scriptname`= 'npc_fl_cloudburst'  WHERE `entry`= 54147;
UPDATE `creature_template` SET `speed_walk`= 1, `speed_run`= 0.142857 WHERE `entry` IN (53800, 53801, 53802);

-- Spell Script Names
DELETE FROM `spell_script_names` WHERE spell_id IN (99012, 99054, 99126, 100985, 100171, 100605, 100503, 100567, 100653, 101237, 100171, 99171,
 100172, 100173, 100174, 98518, 100252, 100253, 100254, 100713, 101015);
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(100605, 'spell_fl_empower_sulfuras'),
(99012, 'spell_fl_splitting_blow'),
(99054, 'spell_fl_invoke_sons'),
(99126, 'spell_fl_blazing_heat'),
(100985, 'spell_fl_blazing_heat'),
(100503, 'spell_fl_breadth_of_frost'),
(100567, 'spell_fl_breadth_of_frost_freeze'),
(100653, 'spell_fl_entrapping_roots'),
(101237, 'spell_fl_entrapping_roots'),
(99171, 'spell_fl_world_in_flames'),
(100172, 'spell_fl_world_in_flames'),
(100173, 'spell_fl_world_in_flames'),
(100174, 'spell_fl_world_in_flames'),
(98518, 'spell_fl_molten_inferno'),
(100252, 'spell_fl_molten_inferno'),
(100253, 'spell_fl_molten_inferno'),
(100254, 'spell_fl_molten_inferno'),
(100713, 'spell_fl_deluge'),
(101015, 'spell_fl_deluge'),
(101088, 'spell_fl_lavalogged'),
(101102, 'spell_fl_lavalogged');

DELETE FROM `spelldifficulty_dbc` WHERE `id` IN (99235, 99236, 99172);
INSERT INTO `spelldifficulty_dbc` (`id`, `spellid0`, `spellid1`, `spellid2`, `spellid3`) VALUES
(99235, 99235, 100178, 100179, 100180),
(99236, 99236, 100181, 100182, 100183),
(99172, 99172, 100175, 100176, 100177);

-- Encounter Texts
DELETE FROM `creature_text` WHERE entry IN (52409, 53875, 53872, 53876);
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
(52409, 0, 0, 'Mortal insects! You dare trespass into MY domain? Your arrogance will be purged in living flame.', 14, 0, 100, 0, 0, 24517, 'Ragnaros - Intro'),
(52409, 1, 0, 'Too soon!... You have come too soon...', 14, 0, 100, 0, 0, 24519, 'Ragnaros - Death Normal Mode'),
(52409, 2, 0, 'No, noooo- This was to be my hour of triumph...', 14, 0, 100, 0, 0, 24518, 'Ragnaros - Death Heroic Mode'),
(52409, 3, 0, 'This is MY realm!', 14, 0, 100, 0, 0, 24529, 'Ragnaros - Kill 1'),
(52409, 3, 1, 'Pathetic.', 14, 0, 100, 0, 0, 24530, 'Ragnaros - Kill 2'),
(52409, 3, 2, 'Die, insect!', 14, 0, 100, 0, 0, 24531, 'Ragnaros - Kill 3'),
(52409, 4, 0, '|TInterface\\Icons\\spell_fire_ragnaros_splittingblow.blp:20|t%s begins to cast |cFFFF0000|Hspell:98951|h''Splitting Blow''|h|r !', 41, 0, 100, 0, 0, 24520, 'Ragnaros - Announce Splitting Blow'),
(52409, 5, 0, 'You will be destroyed!', 14, 0, 100, 0, 0, 24520, 'Ragnaros - Hammer Drop 1'),
(52409, 5, 1, 'Die!', 14, 0, 100, 0, 0, 24521, 'Ragnaros - Hammer Drop 2'),
(52409, 5, 2, 'Your judgement has come!', 14, 0, 100, 0, 0, 24522, 'Ragnaros - Hammer Drop 3'),
(52409, 6, 0, 'Enough! I will finish this!', 14, 0, 100, 0, 0, 24523, 'Ragnaros - Hammer Pickup 1'),
(52409, 6, 1, 'Fall to your knees, mortals! This ends now!', 14, 0, 100, 0, 0, 24524, 'Ragnaros - Hammer Pickup 2'),
(52409, 6, 2, 'Sulfuras will be your end!', 14, 0, 100, 0, 0, 24525, 'Ragnaros - Hammer Pickup 3'),
(52409, 7, 0, 'Come forth, my servants, defend your master!', 14, 0, 100, 0, 0, 24513, 'Ragnaros - Sons of Flame 1'),
(52409, 7, 1, 'Minions of fire! Purge the outsiders!', 14, 0, 100, 0, 0, 24514, 'Ragnaros - Sons of Flame 2'),
(52409, 8, 0, 'Denizens of flame, come to me!', 14, 0, 100, 0, 0, 24515, 'Ragnaros - Sons of Flame 3'),
(52409, 8, 1, 'Arise, servants of fire, consume their flesh!', 14, 0, 100, 0, 0, 24516, 'Ragnaros - Sons of Flame 4'),
(52409, 9, 0, '%s prepares to |cFFFF0000emerge|r!', 41, 0, 100, 0, 0, 0, 'Ragnaros - Announce Emerge'),
(52409, 10, 0, '|TInterface\\Icons\\spell_fire_selfdestruct.blp:20|t%s casts |cFFFF6600|Hspell:98164|h''Magma Trap''|h|r!', 41, 0, 100, 0, 0, 0, 'Ragnaros - Magma Trap'),
(52409, 11, 0, '|TInterface\\Icons\\spell_shaman_lavasurge.blp:20|t%s begins to cast |cFFFF0000|Hspell:98710|h''Sulfuras Smash''|h|r!', 41, 0, 100, 0, 0, 0, 'Ragnaros - Sulfuras Smash'),
(52409, 12, 0, 'Too soon…', 14, 0, 100, 0, 0, 24528, 'Ragnaros - Flee Heroic'),
(52409, 13, 0, 'Arrggh, outsiders - this is not your realm!', 14, 0, 100, 0, 0, 24527, 'Ragnaros - Not Your Realm'),
(52409, 14, 0, 'When I finish this, your pathetic mortal world will burn with my vengeance!', 14, 0, 100, 0, 0, 24526, 'Ragnaros - Standup'),
(52409, 15, 0, '|TInterface\\Icons\\ability_mage_worldinflames.blp:20|t%s begins to cast |cFFFF6600|Hspell:99171|h''Engulfing Flames''|h|r!', 41, 0, 100, 0, 0, 0, 'Ragnaros - Engulfing Flames'),
(52409, 16, 0, '|TInterface\\Icons\\ability_mage_worldinflames.blp:20|t%s begins to cast |cFFFF6600|Hspell:100171|h''World In Flames''|h|r!', 41, 0, 100, 0, 0, 0, 'Ragnaros - World in Flames'),
(52409, 17, 0, '|TInterface\\Icons\\inv_mace_2h_sulfuras_d_01.blp:20|t%s begins to cast |cFFFF6600|Hspell:100604|h''Empower Sulfuras''|h|r!', 41, 0, 100, 0, 0, 0, 'Ragnaros - Empower Sulfuras'),
(52409, 18, 0, '|TInterface\\Icons\\ability_mage_firestarter.blp:20|t%s casts |cFFFF0000|Hspell:100675|h''Dreadflame''|h|r!', 41, 0, 100, 0, 0, 0, 'Ragnaros - Dreadflame'),
(53875, 0, 0, 'Heroes! He is bound. Finish it!', 14, 0, 100, 0, 0, 25169, 'Malfurion - Talk'),
(53875, 1, 0, 'It is finished then!', 14, 0, 100, 0, 0, 25170, 'Malfurion - Talk Outro 1'),
(53875, 2, 0, 'Heroes, the world owns you a great debt.', 14, 0, 100, 0, 0, 25171, 'Malfurion - Talk Outro 2'),
(53872, 0, 0, 'No, fiend. Your time is NOW.', 14, 0, 100, 0, 0, 25159, 'Cenarius - Taunt Ragnaros'),
(53872, 1, 0, 'Perhaps...', 14, 0, 100, 0, 0, 25160, 'Cenarius - Talk Outro 1'),
(53872, 2, 0, 'Ragnaros has perished. But the primal powers he represents can never be vanquished. Another will rise to power, someday.', 14, 0, 100, 0, 0, 25158, 'Cenarius - Talk Outro 3'),
(53872, 3, 0, 'Indeed.', 14, 0, 100, 0, 0, 25161, 'Cenarius - Talk Outro 2'),
(53876, 0, 0, 'Yes, Cenarius. We must maintain a constant vigil over this realm. For let us celebrate this day, and the great victory we have earned here.', 14, 0, 100, 0, 0, 25168, 'Hamuul - Talk Outro 1');

-- Conditions for some spell targets
DELETE FROM conditions WHERE SourceEntry IN (98710, 98953, 98952, 98951, 99056, 99050, 99172, 99235, 99236, 99054, 99012, 99216, 99217, 99218, 99125, 100344, 100342, 100345, 100907, 100891, 100884, 100878, 100881, 100176, 100179, 100182,
101088, 101102, 100605, 100606, 100653, 101237, 100567, 100158, 100302);
INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, SourceEntry, SourceId, ElseGroup, ConditionTypeOrReference, ConditionTarget, ConditionValue1, ConditionValue2, ConditionValue3, NegativeCondition, ErrorType, ScriptName, Comment) VALUES
(13, 1, 100606, 0, 0, 31, 0, 3, 52409, 0, 0, 0, '', 'Empower Sulfuras - Visual Missile Target Ragnaros'),
(13, 1, 100605, 0, 0, 31, 0, 3, 53186, 0, 0, 0, '', 'Empower Sulfuras - Visual Target Molten Seed caster'),
(13, 1, 101088, 0, 0, 31, 0, 3, 53500, 0, 0, 0, '', 'Lava Wave - Target Living Meteor'),
(13, 1, 101102, 0, 0, 31, 0, 3, 53500, 0, 0, 0, '', 'Lava Wave - Target Living Meteor'),
(13, 1, 98710, 0, 0, 31, 0, 3, 53268, 0, 0, 0, '', 'Sulfuras Smash - Target Dummy'),
(13, 1, 100891, 0, 0, 31, 0, 3, 53268, 0, 0, 0, '', 'Sulfuras Smash - Target Dummy'),
(13, 1, 98951, 0, 0, 31, 0, 3, 53393, 0, 0, 0, '', 'Splitting Blow - Target Dummy'),
(13, 1, 98952, 0, 0, 31, 0, 3, 53393, 0, 0, 0, '', 'Splitting Blow - Target Dummy'),
(13, 1, 98953, 0, 0, 31, 0, 3, 53393, 0, 0, 0, '', 'Splitting Blow - Target Dummy'),
(13, 1, 100884, 0, 0, 31, 0, 3, 53393, 0, 0, 0, '', 'Splitting Blow - Target Dummy'),
(13, 1, 100878, 0, 0, 31, 0, 3, 53393, 0, 0, 0, '', 'Splitting Blow - Target Dummy'),
(13, 1, 100881, 0, 0, 31, 0, 3, 53393, 0, 0, 0, '', 'Splitting Blow - Target Dummy'),
(13, 1, 99012, 0, 0, 31, 0, 3, 53393, 0, 0, 0, '', 'Splitting Blow Trigger Missile - Target Dummy'),
(13, 1, 99054, 0, 0, 31, 0, 3, 53140, 0, 0, 0, '', 'Invoke Sons - Target Son of Flame'),
(13, 1, 99216, 0, 0, 31, 0, 3, 53485, 0, 0, 0, '', 'Engulfing Flames - Melee Visual'),
(13, 1, 99172, 0, 0, 31, 0, 3, 53485, 0, 0, 0, '', 'Engulfing Flames - Melee Damage'),
(13, 1, 99217, 0, 0, 31, 0, 3, 53485, 0, 0, 0, '', 'Engulfing Flames - Center Visual'),
(13, 1, 99235, 0, 0, 31, 0, 3, 53485, 0, 0, 0, '', 'Engulfing Flames - Center Damage'),
(13, 1, 99218, 0, 0, 31, 0, 3, 53485, 0, 0, 0, '', 'Engulfing Flames - Range Visual'),
(13, 1, 99236, 0, 0, 31, 0, 3, 53485, 0, 0, 0, '', 'Engulfing Flames - Range Damage'),
(13, 1, 100176, 0, 0, 31, 0, 3, 53485, 0, 0, 0, '', 'Engulfing Flames - Melee Damage'),
(13, 1, 100179, 0, 0, 31, 0, 3, 53485, 0, 0, 0, '', 'Engulfing Flames - Center Damage'),
(13, 1, 100182, 0, 0, 31, 0, 3, 53485, 0, 0, 0, '', 'Engulfing Flames - Range Damage'),
(13, 1, 99125, 0, 0, 31, 0, 3, 53473, 0, 0, 0, '', 'Blazing Heat - Target Dummy'),
(13, 1, 100344, 0, 0, 31, 0, 3, 52409, 0, 0, 0, '', 'Hamuul Draw Firelord - Target Ragnaros'),
(13, 1, 100342, 0, 0, 31, 0, 3, 52409, 0, 0, 0, '', 'Malfurion Draw Firelord - Target Ragnaros'),
(13, 1, 100345, 0, 0, 31, 0, 3, 52409, 0, 0, 0, '', 'Cenarius Draw Firelord - Target Ragnaros'),
(13, 1, 100907, 0, 0, 31, 0, 3, 53500, 0, 0, 0, '', 'Freeze Meteors - Target Living Meteors'),
(13, 7, 100653, 0, 0, 31, 0, 3, 52409, 0, 0, 0, '', 'Entrapping Roots - Target Ragnaros'),
(13, 7, 101237, 0, 0, 31, 0, 3, 52409, 0, 0, 0, '', 'Entrapping Roots - Target Ragnaros'),
(13, 7, 100567, 0, 0, 31, 0, 3, 53500, 0, 0, 0, '', 'Breadth of Frost - Target Meteor'),
(13, 7, 100158, 0, 0, 31, 0, 3, 53189, 0, 0, 0, '', 'Molten Power - Target Molten Elemental'),
(13, 7, 100302, 0, 0, 31, 0, 3, 53189, 0, 0, 0, '', 'Molten Power - Target Molten Elemental');

REPLACE INTO `creature_template_addon` (`entry`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES
(53801, 0, 0, 0, 1, 0, '21857 19818'),
(54127, 0, 0, 0, 1, 0, '100695 100696');

-- Linked spells for Molten Seed to supress code size
DELETE FROM `spell_linked_spell` WHERE `spell_trigger` IN (-98520, -100888);
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES
('-98520', '-100153', '0', 'Molten Elemental - Remove Invisibility'),
('-98520', '98518', '0', 'Molten Elemental - Cast Molten Inferno'),
('-98520', '100157', '0', 'Molten Elemental - Cast Molten Aura'),
('-100888', '-100153', '0', 'Molten Elemental - Remove Invisibility'),
('-100888', '98518', '0', 'Molten Elemental - Cast Molten Inferno'),
('-100888', '100157', '0', 'Molten Elemental - Cast Molten Aura');

DELETE FROM `spell_target_position` WHERE `id`= 100679;
INSERT INTO `spell_target_position` (`id`, `effIndex`, `target_map`, `target_position_x`, `target_position_y`, `target_position_z`, `target_orientation`) VALUES
(100679, 0, 720, 1041.25, -57.4478, 55.5, 0);

REPLACE INTO `creature_model_info` (`modelid`, `bounding_radius`, `combat_reach`) VALUES
(38570, 0.75, 21.0); -- Ragnaros Transformed Model

-- Currency Drop for Ragnaros
DELETE FROM `creature_onkill_reward` WHERE `creature_id` IN (52409, 53797, 53798, 53799);
INSERT INTO `creature_onkill_reward` (`creature_id`, `RewOnKillRepFaction1`, `MaxStanding1`, `RewOnKillRepValue1`, `CurrencyId1`, `CurrencyCount1`) VALUES
-- (52409, 1204, 7, 440, 396, 120), -- 10 Player Normal
-- (53797, 1204, 7, 440, 396, 140), -- 25 Player Normal
(53798, 1204, 7, 800, 396, 120), -- 10 Player Heroic
(53799, 1204, 7, 800, 396, 140); -- 25 Player Heroic

UPDATE `creature_template` SET `baseattacktime`= 1500 WHERE `entry` IN (53189, 53810, 53811, 53812);

-- Localization: German
DELETE FROM `locales_creature_text` WHERE entry IN (52409, 53875, 53872, 53876);
INSERT INTO `locales_creature_text` (`entry`, `groupid`, `id`, `text_loc3`) VALUES
(52409, 0, 0, 'Sterbliche Insekten! Ihr wagt es, in MEIN Reich einzudringen? Eure Arroganz wird in den lodernden Flammen vergehen.'),
(52409, 1, 0, 'Zu früh!... Ihr kommt zu früh...'),
(52409, 2, 0, 'Nein, neiiiin- Dies sollte die Stunde meines Triumphes sein...'),
(52409, 3, 0, 'Das ist MEIN Reich!'),
(52409, 3, 1, 'Erbärmlich.'),
(52409, 3, 2, 'Sterbt, Insekt!'),
(52409, 4, 0, '|TInterface\\Icons\\spell_fire_ragnaros_splittingblow.blp:20|t%s beginnt, |cFFFF0000|Hspell:98951|h''Spaltender Schlag''|h|r zu wirken!'),
(52409, 5, 0, 'Ihr werdet zermalmt!'),
(52409, 5, 1, 'Sterbt!'),
(52409, 5, 2, 'Die Zeit Eurer Abrechnung ist gekommen!'),
(52409, 6, 0, 'Genug! Ich werde dem ein Ende machen.'),
(52409, 6, 1, 'Auf die Knie, Sterbliche! Das ist das Ende.'),
(52409, 6, 2, 'Sulfuras wird Euer Ende sein!'),
(52409, 7, 0, 'Kommt hervor, meine Diener! Verteidigt Euren Meister!'),
(52409, 7, 1, 'Diener des Feuers! Vernichtet die Eindringlinge!'),
(52409, 8, 0, 'Kreaturen der Flamme, kommt zu mir!'),
(52409, 8, 1, 'Erhebt Euch, Diener des Feuers, verzehrt ihr Fleisch!'),
(52409, 9, 0, '%s ist im Begriff, |cFFFF0000aufzutauchen|r!'),
(52409, 10, 0, '|TInterface\\Icons\\spell_fire_selfdestruct.blp:20|t%s wirkt |cFFFF6600|Hspell:98164|h''Magmafalle''|h|r!'),
(52409, 11, 0, '|TInterface\\Icons\\spell_shaman_lavasurge.blp:20|t%s beginnt, |cFFFF0000|Hspell:98710|h''Sulfurasschmettern''|h|r zu wirken!'),
(52409, 12, 0, 'Zu früh!…'),
(52409, 13, 0, 'Arrggh, Eindringlinge - das ist nicht Euer Reich!'),
(52409, 14, 0, 'Wenn ich hiermit fertig bin, wird Eure armselige sterbliche Welt mit meiner Rache brennen!'),
(52409, 15, 0, '|TInterface\\Icons\\ability_mage_worldinflames.blp:20|t%s beginnt, |cFFFF6600|Hspell:99171|h''Einhüllende Flammen''|h|r zu wirken!'),
(52409, 16, 0, '|TInterface\\Icons\\ability_mage_worldinflames.blp:20|t%s beginnt, |cFFFF6600|Hspell:100171|h''Welt in Flammen''|h|r zu wirken!'),
(52409, 17, 0, '|TInterface\\Icons\\inv_mace_2h_sulfuras_d_01.blp:20|t%s beginnt, |cFFFF6600|Hspell:100604|h''Sulfuras mit Macht erfüllen''|h|r zu wirken!'),
(52409, 18, 0, '|TInterface\\Icons\\ability_mage_firestarter.blp:20|t%s beginnt, |cFFFF0000|Hspell:100675|h''Schreckenslohe''|h|r zu wirken!'),
(53875, 0, 0, 'Helden! Er ist gefangen. Bringt es zu Ende!'),
(53875, 1, 0, 'Es ist also vollbracht!'),
(53875, 2, 0, 'Helden, die Welt steht tief in Eurer Schuld.'),
(53872, 0, 0, 'Nein, Scheusal. Eure Zeit ist GEKOMMEN.'),
(53872, 1, 0, 'Vielleicht...'),
(53872, 2, 0, 'Ragnaros ist besiegt. Doch die Urgewalten für die er stand, können nie besiegt werden. Eines Tages wird ein anderer seinen Platz einnehmen.'),
(53872, 3, 0, 'In der Tat.'),
(53876, 0, 0, 'Ja, Cenarius. Wir müssen stets ein wachsames Auge auf dieses Reich haben. Doch lasst uns diesen Tag und den Sieg, den wir hier errungen haben, feiern.');
