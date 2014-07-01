-- Erudax
UPDATE `creature_template` SET `minlevel`= 86, `maxlevel`= 86, `faction_A`= 16, `faction_H`= 16, `exp`= 3, `rank`= 3, `mechanic_immune_mask`= 667893759, `scriptname`= 'boss_erudax' WHERE `entry`= 40484;
UPDATE `creature_template` SET `minlevel`= 87, `maxlevel`= 87, `faction_A`= 16, `faction_H`= 16, `exp`= 3, `rank`= 3, `mechanic_immune_mask`= 667893759 WHERE `entry`= 48822;
-- Shadow Gale Stalker
UPDATE `creature_template` SET `minlevel`= 87, `maxlevel`= 87, `faction_A`= 7, `faction_H`= 7, `unit_flags`= 33554432, `flags_extra`= 131, `scriptname`= 'npc_gb_shadow_gale_stalker' WHERE `entry`= 40567;
-- Portal Stalker
UPDATE `creature_template` SET `unit_flags`= 33554432, `flags_extra`= 131 WHERE `entry`= 44314;
UPDATE `creature_template_addon` SET `auras`= '' WHERE `entry`= 44314;
UPDATE `creature` SET `phasemask` = 1 WHERE `guid` = 222041;
-- Faceless Corruptors
UPDATE `creature_template` SET `minlevel`= 84, `maxlevel`= 84, `faction_A`= 16, `faction_H`= 16, `exp`= 3, `mechanic_immune_mask`= 634339327, `scriptname`= 'npc_gb_faceless_corruptor' WHERE `entry`= 40600;
UPDATE `creature_template` SET `minlevel`= 84, `maxlevel`= 84, `faction_A`= 16, `faction_H`= 16, `exp`= 3, `mechanic_immune_mask`= 634339327, `scriptname`= 'npc_gb_faceless_corruptor' WHERE `entry`= 48844;
UPDATE `creature_template` SET `minlevel`= 85, `maxlevel`= 85, `faction_A`= 16, `faction_H`= 16, `exp`= 3 WHERE `entry`= 48828;
UPDATE `creature_template` SET `minlevel`= 85, `maxlevel`= 85, `faction_A`= 16, `faction_H`= 16, `exp`= 3 WHERE `entry`= 48845;
-- Alextraszas Egg
UPDATE `creature_template` SET `minlevel`= 85, `maxlevel`= 85, `faction_A`= 35, `faction_H`= 35, `exp`= 3, `scriptname`= 'npc_gb_alexstraszas_egg' WHERE `entry`= 40486;
UPDATE `creature_template` SET `minlevel`= 85, `maxlevel`= 85, `faction_A`= 35, `faction_H`= 35, `exp`= 3, `unit_flags`= 256 WHERE `entry`= 40846;
-- Twilight Hatchlings
UPDATE `creature_template` SET `minlevel`= 84, `maxlevel`= 84, `faction_A`= 14, `faction_H`= 14, `unit_flags`= 33554432, `InhabitType`= 4, `scriptname`= 'npc_gb_twilight_hatchling' WHERE `entry`= 39388;
UPDATE `creature_template` SET `minlevel`= 85, `maxlevel`= 85, `faction_A`= 14, `faction_H`= 14, `unit_flags`= 33554432,`InhabitType`= 4 WHERE `entry`= 48832;

REPLACE INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
(40484, 0, 0, 'The darkest days are still ahead!', 14, 0, 100, 0, 0, 18638, 'Erudax - Aggro'),
(40484, 1, 0, '|TInterface\\Icons\\spell_shadow_shadowfury.blp:20|t%s begins to cast |cFFA043E7|Hspell:75694|h[Shadow Gale]|h|r!', 41, 0, 100, 0, 0, 0, 'Erudax - Announce Shadow Gale'),
(40484, 2, 0, 'F\'lakh ghet! The shadow\'s hunger cannot be sated!', 14, 0, 100, 0, 0, 18644, 'Erudax - Shadow Gale'),
(40484, 3, 0, 'Come, suffering... Enter, chaos!', 14, 0, 100, 0, 0, 18646, 'Erudax to Erudax'),
(40484, 4, 0, '%s summons a |cFFFF0000Faceless Guardian|r!', 41, 0, 100, 0, 0, 0, 'Erudax to Erudax'),
(40484, 5, 0, '|TInterface\\Icons\\spell_shadow_sacrificialshield.blp:20|t%s begins to cast |cFF006EFD|Hspell:75809|h[Shield of Nightmares]|h|r on the |cFF006EFDFaceless Corruptor|r!', 41, 0, 100, 0, 0, 0, 'Erudax - Shield of Nightmares'),
(40484, 6, 0, 'Flesh for the offering!', 14, 0, 100, 0, 0, 18640, 'Erudax - Slay 1'),
(40484, 6, 1, 'Erudax cackles maniacally.', 16, 0, 100, 0, 0, 18639, 'Erudax - Slay 2'),
(40484, 7, 0, 'Ywaq maq oou; ywaq maq ssaggh. Yawq ma shg\'fhn.', 14, 0, 100, 0, 0, 18641, 'Erudax - Death');

REPLACE INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(75656, 'spell_gb_shadow_gale_trigger'),
(75692, 'spell_gb_shadow_gale'),
(91087, 'spell_gb_shadow_gale'),
(75694, 'spell_gb_shadow_gale_aura'),
(76194, 'spell_gb_twilight_blast'),
(91042, 'spell_gb_twilight_blast');

DELETE FROM `conditions` WHERE `SourceEntry` IN (75656, 75664, 91086, 75809, 75520, 91049, 75763, 91040);
INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, SourceEntry, SourceId, ElseGroup, ConditionTypeOrReference, ConditionTarget, ConditionValue1, ConditionValue2, ConditionValue3, NegativeCondition, ErrorType, ScriptName, Comment) VALUES
(13, 7, 75656, 0, 0, 31, 0, 3, 40566, 0, 0, 0, '', 'Shadow Gale Trigger - Target Shadow Gale Controller'),
(13, 7, 75664, 0, 0, 31, 0, 3, 40567, 0, 0, 0, '', 'Shadow Gale - Target Shadow Gale Stalker'),
(13, 7, 91086, 0, 0, 31, 0, 3, 40567, 0, 0, 0, '', 'Shadow Gale - Target Shadow Gale Stalker'),
(13, 7, 75809, 0, 0, 31, 0, 3, 40600, 0, 0, 0, '', 'Shield of Nightmares - Target Faceless Corruptor 1'),
(13, 7, 75809, 0, 0, 31, 0, 3, 48844, 0, 0, 0, '', 'Shield of Nightmares - Target Faceless Corruptor 2'),
(13, 1, 75520, 0, 0, 31, 0, 3, 40486, 0, 0, 0, '', 'Twilight Corruption - Target Alexstraszas Egg'),
(13, 1, 91049, 0, 0, 31, 0, 3, 40486, 0, 0, 0, '', 'Twilight Corruption - Target Alexstraszas Egg'),
(13, 1, 75763, 0, 0, 31, 0, 3, 40484, 0, 0, 0, '', 'Umbral Mending - Target Erudax'),
(13, 1, 91040, 0, 0, 31, 0, 3, 40484, 0, 0, 0, '', 'Umbral Mending - Target Erudax');

REPLACE INTO `spell_target_position` (`id`, `effIndex`, `target_map`, `target_position_x`, `target_position_y`, `target_position_z`, `target_orientation`) VALUES
(75704, 0, 670, -620.443, -827.19, 241.774, 3.184877),
(91072, 0, 670, -620.443, -827.19, 241.774, 3.184877),
(91072, 1, 670, -620.443, -827.19, 241.774, 3.184877);
