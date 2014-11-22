-- Altairus
UPDATE `creature_template` SET `HoverHeight`= 10.125, `movementId`= 167, `InhabitType`= 4, `mingold`= 17500, `maxgold`= 17600 WHERE `entry` IN (43873, 43874);
UPDATE `creature_template` SET `InhabitType`= 4 WHERE `entry`= 47305;
REPLACE INTO `creature_onkill_reward` (`creature_id`, `CurrencyId1`, `CurrencyCount1`) VALUES
(43874, 395, 70);

-- Twister
UPDATE `creature_template` SET `minlevel`= 85, `maxlevel`= 85, `faction_A`= 14, `faction_H`= 14, `speed_walk`= 0.8, `speed_run`= 0.2857143, `unit_flags`= 33587200, `flags_extra`= 128, `HoverHeight`= 0, `InhabitType`= 1,  `scriptname`= '' WHERE `entry`= 47342;
UPDATE `creature` SET `MovementType`= 1, `spawndist`= 8 WHERE `id`= 47342;
-- Air Current
UPDATE `creature` SET `MovementType`= 0, `spawndist`= 0 WHERE `id`= 47305;

REPLACE INTO `creature_template_addon` (`entry`, `bytes1`, `bytes2`, `auras`) VALUES
(47342, 0, 0, ''), -- Twister Aura
(42844, 0, 0, '88350'), -- Invisible Stalker (Cataclysm Boss, Ignore Combat) - Safe Area
(43873, 0x2000000, 0x1, ''); -- Altairus

REPLACE INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(88282, 'spell_vp_upwind_of_altairus'),
(88322, 'spell_vp_chilling_breath'),
(88276, 'spell_vp_call_the_wind'),
(88772, 'spell_vp_call_the_wind_channeled');

DELETE FROM `conditions` WHERE `SourceEntry` IN (88276, 88772, 88244);
INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, SourceEntry, SourceId, ElseGroup, ConditionTypeOrReference, ConditionTarget, ConditionValue1, ConditionValue2, ConditionValue3, NegativeCondition, ErrorType, ScriptName, Comment) VALUES
(13, 7, 88276, 0, 0, 31, 0, 3, 47305, 0, 0, 0, '', 'Call the Wind - Target Air Current Dummy'),
(13, 7, 88772, 0, 0, 31, 0, 3, 47305, 0, 0, 0, '', 'Call the Wind - Target Air Current Dummy');
