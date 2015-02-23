REPLACE INTO `areatrigger_scripts` (`entry`, `ScriptName`) VALUES
(6625, 'at_ascendant_council_1'),
(6626, 'at_ascendant_council_2'),
(6627, 'at_ascendant_council_3');

UPDATE `creature_template` SET `scriptname`= 'npc_ascendant_council_controller', `minlevel`= 80, `maxlevel`= 80, `faction`= 14, `unit_flags`= 33554432 WHERE `entry`= 43691;
UPDATE `creature_template` SET `scriptname`= 'boss_feludius', `speed_walk`= 4, `BaseAttackTime`= 1500, `difficulty_entry_1`= 49612, `difficulty_entry_2`= 49613, `difficulty_entry_3`= 49614, `AIName`= '' WHERE `entry`= 43687;
UPDATE `creature_template` SET `scriptname`= 'boss_ignacious', `speed_walk`= 4, `BaseAttackTime`= 1500, `difficulty_entry_1`= 49615, `difficulty_entry_2`= 49616, `difficulty_entry_3`= 49617, `AIName`= '' WHERE `entry`= 43686;
UPDATE `creature_template` SET `scriptname`= 'boss_arion', `speed_walk`= 4, `BaseAttackTime`= 1500, `difficulty_entry_1`= 49606, `difficulty_entry_2`= 49607, `difficulty_entry_3`= 49608, `AIName`= '' WHERE `entry`= 43688;
UPDATE `creature_template` SET `scriptname`= 'boss_terrastra', `speed_walk`= 4, `BaseAttackTime`= 1500, `difficulty_entry_1`= 49609, `difficulty_entry_2`= 49610, `difficulty_entry_3`= 49611, `AIName`= '' WHERE `entry`= 43689;
UPDATE `creature_template` SET `scriptname`= 'boss_elementium_monstrosity', `difficulty_entry_1`= 49619, `difficulty_entry_2`= 49620, `difficulty_entry_3`= 49621, `AIName`= '' WHERE `entry`= 43735;

DELETE FROM `creature_template_addon` WHERE `entry` IN (43686, 43687, 43688, 43689);

-- Water Bomb
UPDATE `creature_template` SET `minlevel`= 80, `maxlevel`= 80, `faction`= 14, `unit_flags`= 33554432, `flags_extra`= 128, `InhabitType`= 4 WHERE `entry`= 44201;
-- Inferno Rush
UPDATE `creature_template` SET `minlevel`= 80, `maxlevel`= 80, `faction`= 14, `unit_flags`= 33554432, `flags_extra`= 128, `InhabitType`= 4 WHERE `entry`= 47501;
-- Violent Cyclone
UPDATE `creature_template` SET `minlevel`= 87, `maxlevel`= 87, `faction`= 1847, `unit_flags`= 33554432, `flags_extra`= 128 WHERE `entry`= 44747;
-- Feludius and Ignacious and Terrastra
UPDATE `creature_template` SET `minlevel`= 88, `maxlevel`= 88, `faction`= 16, `BaseAttackTime`= 1500, `speed_walk`= 4, `mechanic_immune_mask`= 617299839, `exp`= 3 WHERE `entry` IN (49612, 49613, 49614, 49615, 49616, 49617, 43686, 43687, 43689, 49609, 49610, 49611);
-- Arion
UPDATE `creature_template` SET `minlevel`= 88, `maxlevel`= 88, `faction`= 16, `BaseAttackTime`= 1500, `speed_walk`= 4, `mechanic_immune_mask`= 650854399, `exp`= 3 WHERE `entry` IN (49606, 49607, 49608, 43688);
-- Elementium Monstrosity
UPDATE `creature_template` SET `minlevel`= 88, `maxlevel`= 88, `faction`= 16, `BaseAttackTime`= 1500, `mechanic_immune_mask`= 650854399, `exp`= 3 WHERE `entry` IN (43735, 49619, 49620, 49621);
-- Liquid Ice
UPDATE `creature_template` SET `minlevel`= 88, `maxlevel`= 88, `faction`= 14, `unit_flags`= 33554432, `flags_extra`= 128 WHERE `entry`= 45452;
-- Eruption target
UPDATE `creature_template` SET `minlevel`= 70, `maxlevel`= 70, `faction`= 114, `unit_flags`= 33554432, `flags_extra`= 128 WHERE `entry`= 44845;
-- Ascendant Council Plume Stalker
UPDATE `creature_template` SET `minlevel`= 80, `maxlevel`= 80, `faction`= 14, `unit_flags`= 33554432, `flags_extra`= 128, `scriptname`= 'npc_ac_plume_stalker' WHERE `entry`= 45420;
-- Gravity Crush
UPDATE `creature_template` SET `minlevel`= 80, `maxlevel`= 80, `faction`= 14, `unit_flags`= 34079232, `flags_extra`= 128, `vehicleId`= 1110, `InhabitType`= 4 WHERE `entry`= 45476;
-- Gravity Well
UPDATE `creature_template` SET `minlevel`= 87, `maxlevel`= 87, `faction`= 14, `unit_flags`= 33554432, `flags_extra`= 128, `scriptname`= 'npc_ac_gravity_well' WHERE `entry`= 44824;

REPLACE INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
(43324, 4, 0, 'Welcome, mortals. (Frail little children). Few have laid eyes on this inner sanctum. (They reach out to touch the fire!)', 14, 0, 100, 0, 0, 22065, 'Cho''gall - Ascendant Countil Intro'),
(43324, 5, 0, 'It is here the chosen realize their destiny. (One with eternity). And it is here that you will realize yours.(End of the flesh. End of the flesh)!', 14, 0, 100, 0, 0, 22066, 'Cho''gall - Ascendant Countil Intro'),
(43324, 6, 0, 'Brothers of Twilight! The Hammer calls to you! (Fire water earth air). Leave your mortal shell behind. (Fire water earth air). Embrace your new forms for here and everafter! (Burn and drown and crush and suffocate). And use your gifts to destroy the unbelievers. (Burn and drown and crush and suffocate)!!', 14, 0, 100, 0, 0, 22067, 'Cho''gall - Ascendant Countil Intro'),
-- Feludius
(43687, 0, 0, 'You dare invade our lord''s sanctum?', 14, 0, 100, 0, 0, 20162, 'Feludius - Aggro'),
(43687, 1, 0, 'Perish!', 14, 0, 100, 0, 0, 20163, 'Feludius - Slay'),
(43687, 2, 0, 'I will freeze the blood in your veins!', 14, 0, 100, 0, 0, 20164, 'Feludius - Glaciate Say'),
(43687, 3, 0, '%s begins to cast Glaciate!', 41, 0, 100, 0, 0, 0, 'Feludius - Glaciate Accounce'),
(43687, 4, 0, 'But now, witness true power...', 14, 0, 100, 0, 0, 20165, 'Feludius - Fuse Intro'),
-- Ignacious
(43686, 0, 0, 'You will die for your insolence!', 14, 0, 100, 0, 0, 20285, 'Ignacious - Aggro'),
(43686, 1, 0, 'More fuel for the fire!', 14, 0, 100, 0, 0, 20286, 'Ignacious - Slay'),
(43686, 2, 0, 'BURN!', 14, 0, 100, 0, 0, 20287, 'Ignacious - Rising Flames Say'),
(43686, 3, 0, '%s begins to cast Rising Flames!', 41, 0, 100, 0, 0, 0, 'Ignacious - Rising Flames Accounce'),
(43686, 4, 0, '...the fury of the elements!', 14, 0, 100, 0, 0, 20288, 'Ignacious - Fuse Intro'),
-- Arion
(43688, 0, 0, 'Enough of this foolishness!', 14, 0, 100, 0, 0, 20237, 'Arion - Aggro'),
(43688, 1, 0, 'Merely a whisper in the wind....', 14, 0, 100, 0, 0, 20238, 'Arion - Slay'),
(43688, 2, 0, 'Wind, hear my call!', 14, 0, 100, 0, 0, 20239, 'Arion - Call Winds'),
(43688, 3, 0, '%s begins to cast Thundershock!', 41, 0, 100, 0, 0, 0, 'Arion - Thundershock Accounce'),
(43688, 4, 0, 'An impressive display...', 14, 0, 100, 0, 0, 20240, 'Arion - Fuse Intro'),
-- Terrastra
(43689, 0, 0, 'We will handle them!', 14, 0, 100, 0, 0, 21843, 'Terrastra - Aggro'),
(43689, 1, 0, 'The soil welcomes your bones!', 14, 0, 100, 0, 0, 21842, 'Terrastra - Slay'),
(43689, 2, 0, 'The earth will devour you!', 14, 0, 100, 0, 0, 21844, 'Terrastra - Ground Rupture'),
(43689, 3, 0, '%s begins to cast Quake!', 41, 0, 100, 0, 0, 0, 'Terrastra - Quake Accounce'),
(43689, 4, 0, '...to have made it this far.', 14, 0, 100, 0, 0, 21845, 'Terrastra - Fuse Intro'),
-- Elementium Monstrosity
(43735, 0, 0, 'BEHOLD YOUR DOOM!', 14, 0, 100, 0, 0, 20396, 'Elementium Monstrosity - Aggro'),
(43735, 1, 0, 'Eradicate....', 14, 0, 100, 0, 0, 20398, 'Elementium Monstrosity - Slay 1'),
(43735, 1, 1, 'Annihilate....', 14, 0, 100, 0, 0, 20397, 'Elementium Monstrosity - Slay 2'),
(43735, 2, 0, 'FEEL THE POWER!', 14, 0, 100, 0, 0, 20400, 'Elementium Monstrosity - Gravity Crush'),
(43735, 6, 0, 'Impossible....', 14, 0, 100, 0, 0, 20399, 'Elementium Monstrosity - Death'),
-- Ascendant Council Controller
(43691, 0, 0, 'The ground beneath you rumbles ominously...', 41, 0, 100, 0, 0, 0, 'Ascendant Council Controller - Quake'),
(43691, 1, 0, 'The air around you crackles with energy...', 41, 0, 100, 0, 0, 0, 'Ascendant Council Controller - Thundershock');

REPLACE INTO `spell_script_names` (`spell_id`, `scriptname`) VALUES
(82699, 'spell_ac_water_bomb'),
(82746, 'spell_ac_glaciate'),
(92506, 'spell_ac_glaciate'),
(92507, 'spell_ac_glaciate'),
(92508, 'spell_ac_glaciate'),
(82665, 'spell_ac_heart_of_ice'),
(82860, 'spell_ac_inferno_rush_fire'),
(92523, 'spell_ac_inferno_rush_fire'),
(92524, 'spell_ac_inferno_rush_fire'),
(92525, 'spell_ac_inferno_rush_fire'),
(82660, 'spell_ac_burning_blood'),
(84918, 'spell_ac_cryogenic_aura'),
(84915, 'spell_ac_liquid_ice'),
(92497, 'spell_ac_liquid_ice'),
(92498, 'spell_ac_liquid_ice'),
(92499, 'spell_ac_liquid_ice'),
(83675, 'spell_ac_eruption'),
(84527, 'spell_ac_electrical_instability'),
(84948, 'spell_ac_gravity_crush'),
(92486, 'spell_ac_gravity_crush'),
(92487, 'spell_ac_gravity_crush'),
(92488, 'spell_ac_gravity_crush'),
(83498, 'spell_ac_lashing_winds'),
(92476, 'spell_ac_lashing_winds'),
(92477, 'spell_ac_lashing_winds'),
(92478, 'spell_ac_lashing_winds'),
(83565, 'spell_ac_quake'),
(92544, 'spell_ac_quake'),
(92545, 'spell_ac_quake'),
(92546, 'spell_ac_quake'),
(83581, 'spell_ac_grounded'),
(83067, 'spell_ac_thundershock'),
(92469, 'spell_ac_thundershock'),
(92470, 'spell_ac_thundershock'),
(92471, 'spell_ac_thundershock'),
(83099, 'spell_ac_lightning_rod'),
(83087, 'spell_ac_disperse'),
(83718, 'spell_ac_harden_skin'),
(92541, 'spell_ac_harden_skin'),
(92542, 'spell_ac_harden_skin'),
(92543, 'spell_ac_harden_skin'),
(83070, 'spell_ac_lightning_blast'),
(92454, 'spell_ac_lightning_blast'),
(92455, 'spell_ac_lightning_blast'),
(92456, 'spell_ac_lightning_blast'),
(94731, 'spell_ac_lightning_blast_triggered');

DELETE FROM `conditions` WHERE `SourceEntry` IN (82699, 84913, 83087);
INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, SourceEntry, SourceId, ElseGroup, ConditionTypeOrReference, ConditionTarget, ConditionValue1, ConditionValue2, ConditionValue3, NegativeCondition, ErrorType, ScriptName, Comment) VALUES
(13, 7, 82699, 0, 0, 31, 0, 3, 44201, 0, 0, 0, '', 'Water Bomb - Target Water Bomb'),
(13, 7, 84913, 0, 0, 31, 0, 3, 45420, 0, 0, 0, '', 'Lava Seed - Target Plume Stalker'),
(13, 7, 83087, 0, 0, 31, 0, 3, 44553, 0, 0, 0, '', 'Disperse - Target Target Stalker');

REPLACE INTO `creature_template_addon` (`entry`, `auras`) VALUES
(44747 ,'83472'),
(45452, '84914'),
(44845, '83662');

UPDATE `creature` SET `phasemask` = 1 WHERE `guid` = 779687;
UPDATE `creature` SET `phasemask` = 1 WHERE `guid` = 779702;
UPDATE `creature` SET `phasemask` = 1 WHERE `guid` = 779704;
UPDATE `creature` SET `phasemask` = 1 WHERE `guid` = 779703;
UPDATE `creature` SET `phasemask` = 1 WHERE `guid` = 779705;
UPDATE `creature` SET `phasemask` = 1 WHERE `id` IN (45420, 44553);
DELETE FROM `creature` WHERE `id` IN (44201, 50297, 43735, 45476);

-- Pre Trash Group
DELETE FROM `smart_scripts` WHERE `entryorguid` IN (49825, 49817, 49826, 49821);
UPDATE `creature` SET `MovementType`= 1, `spawndist`= 15 WHERE `id` IN (49825, 49817, 49826, 49821);
-- General Updates
UPDATE `creature_template` SET `minlevel`= 87, `maxlevel`= 87, `faction`= 16, `unit_flags`= 32832, `AIName`= '' WHERE `entry`IN (49825, 49817, 49826, 49821);
REPLACE INTO `creature_template_addon` (`entry`, `auras`) VALUES
(49825, '93335'),
(49821, '87906'),
(49817, '93336');
