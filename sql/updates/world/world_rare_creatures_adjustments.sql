UPDATE `creature_template` SET `InhabitType`=4 WHERE `entry`=50061;
UPDATE `creature` SET `phaseMask`=1 WHERE `id` IN (50061, 49822, 50059);