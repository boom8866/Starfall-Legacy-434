-- Gag Order
UPDATE `spell_proc_event` SET `SpellFamilyMask0`='8', `procFlags`='87376' WHERE `entry IN('12311','12958');
UPDATE `spell_proc_event` SET `CustomChance`='50' WHERE `entry` = '12311';
UPDATE `spell_proc_event` SET `CustomChance`='100' WHERE `entry` = '12958';