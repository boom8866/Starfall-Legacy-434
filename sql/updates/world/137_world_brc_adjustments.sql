DELETE FROM `creature_onkill_reward` WHERE `creature_id`=39665;
UPDATE `creature_template` SET `DamageModifier`=15 WHERE `entry` IN (39705, 39700, 39698, 39679, 39665);
