
-- Update Asaad Heroic Inhabit Type
UPDATE `creature_template` SET `InhabitType`= 4 WHERE `entry`= 43876;

-- Update Grounding Field Stalker extra flags for invisibility
UPDATE `creature_template` SET `flags_extra`= 130 WHERE `entry`= 47036;

-- Update Skyfall Star entries
UPDATE `creature_template` SET `minlevel`= 82, `maxlevel`= 82 WHERE `entry`= 52019;
UPDATE `creature_template` SET `minlevel`= 85, `maxlevel`= 85 WHERE `entry`= 52020;
UPDATE `creature_template` SET `faction_A`= 16, `faction_H`= 16 WHERE `entry` IN (52020, 52019);

-- Add Slipstream Spell Script Name
REPLACE INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
('85063', 'spell_slipstream');

-- adding currency for asaad HC
REPLACE INTO `creature_onkill_reward` (`creature_id`, `CurrencyId1`, `CurrencyCount1`) VALUES
(43876, 395, 70);