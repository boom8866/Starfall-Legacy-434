-- General Husam
UPDATE `creature_template` SET `rank`= 3, `mindmg`= 532, `maxdmg`= 798, `attackpower`= 199, `dmg_multiplier`= 20, `flags_extra`= 1 WHERE `entry`= 44577;
UPDATE `creature_template` SET `rank`= 3, `mindmg`= 532, `maxdmg`= 798, `attackpower`= 199, `dmg_multiplier`= 35, `flags_extra`= 1 WHERE `entry`= 48932;
UPDATE `creature_template` SET `mechanic_immune_mask`= 667893759 WHERE `entry` IN (44577, 48932);

-- Lockmaw
UPDATE `creature_template` SET `rank`= 3, `mindmg`= 532, `maxdmg`= 798, `attackpower`= 199, `dmg_multiplier`= 20, `flags_extra`= 1 WHERE `entry`= 43614;
UPDATE `creature_template` SET `rank`= 3, `mindmg`= 532, `maxdmg`= 798, `attackpower`= 199, `dmg_multiplier`= 35, `flags_extra`= 1 WHERE `entry`= 49043;
UPDATE `creature_template` SET `mechanic_immune_mask`= 667893759 WHERE `entry` IN (43614, 49043, 43658, 45379, 45378, 49045);

-- High Prophet Barim
UPDATE `creature_template` SET `rank`= 3, `mindmg`= 532, `maxdmg`= 798, `attackpower`= 199, `dmg_multiplier`= 20, `flags_extra`= 1 WHERE `entry`= 43612;
UPDATE `creature_template` SET `rank`= 3, `mindmg`= 532, `maxdmg`= 798, `attackpower`= 199, `dmg_multiplier`= 35, `flags_extra`= 1 WHERE `entry`= 48951;
UPDATE `creature_template` SET `mechanic_immune_mask`= 667893759 WHERE `entry` IN (43612, 48951, 48906, 43927, 48953, 43934, 48954);
UPDATE `creature_template` SET `exp`= 3 WHERE `entry` IN (48953, 43927);

-- Siamat
UPDATE `creature_template` SET `mechanic_immune_mask`= 667893759 WHERE `entry` IN (44819, 51088, 45259, 45268, 45269, 49256, 49257, 49258, 44704, 49260);
