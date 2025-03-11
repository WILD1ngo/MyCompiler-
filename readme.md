Simple Start

term = <input> | variable | literal
expression = term | term + term | ...
rel = term < term | ...
instr = variable = expression | <if> rel <then> instr | <goto> :label | <output> term |label:



instr' ->instractions 
instractions -> instractions instr
instractions -> instr

instr -> var = expr
instr -> IF rel THEN instr
instr -> label
instr -> goto label
instr -> output term
rel -> term < term
expr -> term
expr -> term + term
term -> input 
term -> var  
term -> INT