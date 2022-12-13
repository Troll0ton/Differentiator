
CMD_DEF(ADD, "+",
{
    curr_node->val.num = LEFT_NUM + RIGHT_NUM;
})

CMD_DEF(SUB, "-",
{
    curr_node->val.num = LEFT_NUM - RIGHT_NUM;
})

CMD_DEF(MUL, "*",
{
    curr_node->val.num = LEFT_NUM * RIGHT_NUM;
})

CMD_DEF(DIV, "/",
{
    curr_node->val.num = LEFT_NUM / RIGHT_NUM;
})

CMD_DEF(POW, "^",
{
    ;
})

CMD_DEF(SIN, "sin",
{
    curr_node->val.num = sin (RIGHT_NUM);
})

CMD_DEF(COS, "cos",
{
    curr_node->val.num = cos (RIGHT_NUM);
})

CMD_DEF(LN, "ln",
{
    ;
})

CMD_DEF(TG, "tg",
{
    ;
})

CMD_DEF(CTG, "ctg",
{
    ;
})

CMD_DEF(ARCSIN, "arcsin",
{
    ;
})

CMD_DEF(ARCCOS, "arccos",
{
    ;
})

CMD_DEF(ARCTG, "arctg",
{
    ;
})

CMD_DEF(ARCCTG, "arcctg",
{
    ;
})
