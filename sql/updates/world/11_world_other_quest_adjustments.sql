UPDATE `creature_template` SET `InhabitType`=4 WHERE `entry`=47422;
UPDATE `creature_template_addon` SET `auras`='' WHERE `entry`=46321;
UPDATE `spell_target_position` SET `target_position_x`=-8507.00, `target_position_y`=-45.32, `target_position_z`=272.48, `target_orientation`=2.74 WHERE `id`=90800 AND `effIndex`=0;
UPDATE `creature` SET `phaseMask`=32768 WHERE `guid`=728614;
UPDATE `creature_template` SET `InhabitType`=4, `flags_extra`=128 WHERE `entry`=48728;