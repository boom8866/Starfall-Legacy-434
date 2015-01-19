UPDATE `creature_template` SET `BaseAttackTime`=0, `RangeAttackTime`=0 WHERE `entry`=35077;
UPDATE `creature_template` SET `DamageModifier`=0.4 WHERE `entry` IN (35456, 35167);