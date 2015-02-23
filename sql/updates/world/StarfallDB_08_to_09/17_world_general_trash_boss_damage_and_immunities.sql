-- Updated all mechanic immunities to prevent boss immune to spells like Infected Wounds
UPDATE `creature_template` SET `mechanic_immune_mask`='617299839' WHERE `mechanic_immune_mask` IN (667893751, 617299967);

-- General Damage Modifier (BASE ADJUST, WE WILL USE IN GAME COMMAND TO FINE TUNE IT)
UPDATE `creature_template` SET `DamageModifier`=41.6 WHERE `DamageModifier` > '55';