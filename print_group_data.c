/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_group_data.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmin <akuzmin@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 23:03:56 by akuzmin           #+#    #+#             */
/*   Updated: 2025/06/02 15:05:53 by akuzmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minichill.h"

// Function to convert token type to string
const char	*token_type_to_str(int type)
{
    switch (type)
    {
        case ASSIGNMENT: return ("ASSIGNMENT");
        case STR: return ("STR");
        case EXPAND_STR: return ("EXPAND_STR");
        case INCMD_ECHO: return ("ECHO");
        case INCMD_CD: return ("CD");
        case INCMD_PWD: return ("PWD");
        case INCMD_EXIT: return ("EXIT");
        case INCMD_EXPORT: return ("EXPORT");
        case INCMD_ENV: return ("ENV");
        case INCMD_UNSET: return ("UNSET");
        case STD_CMD: return ("STD_CMD");
        case PIPE: return ("PIPE");
        case OR: return ("OR");
        case AND: return ("AND");
        case RED_IN: return ("RED_IN");
        case RED_OUT: return ("RED_OUT");
        case HERE_DOC: return ("HERE_DOC");
        case ADD_OUT: return ("ADD_OUT");
        case O_BR: return ("O_BR");
        case C_BR: return ("C_BR");
        case FLAG: return ("FLAG");
        case TEXT: return ("TEXT");
        case BIN_AND: return ("BIN_AND");
        case SMCLN: return ("SEMICOLON(;)");
        // case CLN: return ("COLON(:)");
        default: return ("UNKNOWN");
    }
}

// Function to convert connection type to string
const char	*connection_type_to_str(int type)
{
    switch (type)
    {
        case SMCLN: return ("SMCLN");
        case PIPE: return ("PIPE");
        case OR: return ("OR");
        case AND: return ("AND");
        default: return ("NONE");
    }
}

// Print redirection information
void	print_redirection_info(t_group *group, const char *indent)
{
    size_t	i;

    if (!group || !group->red || group->red->size == 0)
        return ;
    
    // Check if content array is empty
    if (!group->red->content || !group->red->content[0])
        return ;
    
    printf("%sRedirections:\n", indent);
    
    i = 0;
    while (i < group->red->size && i < 100)
    {
        const char	*red_symbol;

        red_symbol = "?";
        if (group->red->type[i] == RED_IN)
            red_symbol = "<";
        else if (group->red->type[i] == RED_OUT)
            red_symbol = ">";
        else if (group->red->type[i] == HERE_DOC)
            red_symbol = "<<";
        else if (group->red->type[i] == ADD_OUT)
            red_symbol = ">>";
        
        printf("%s  └─ %s %s [%s]\n", indent, red_symbol,
            group->red->content[i], 
            token_type_to_str(group->red->type[i]));
        i++;
    }
}

void	print_group(t_group *group, int depth, t_group *parent_to_check)
{
    char		indent[50];
    int			loop_guard;
    t_group		*next;
    const char	*parent_status;

    if (!group)
        return ;
    
    ft_memset(indent, 0, sizeof(indent));
    for (int i = 0; i < depth && i < 20; i++)
        ft_strlcat(indent, "  ", sizeof(indent));
    
    loop_guard = 0;
    while (group && loop_guard < 100)
    {
        loop_guard++;
        
        parent_status = (group->parrent == parent_to_check) ? "✓" : "✗";
        
        printf("%s┌─── Group [%p] ───────────────────\n", 
            indent, (void *)group);
        printf("%s│ Parent: %p %s\n", 
            indent, (void *)group->parrent, parent_status);
        printf("%s│ Connection: %s\n", 
            indent, connection_type_to_str(group->exec_type));
        
        if (!group->data)
        {
            printf("%s│ [EMPTY GROUP]\n", indent);
            printf("%s└───────────────────────────────\n", indent);
            group = group->next;
            continue;
        }
        
        if (group->data_type == GROUP)
        {
            printf("%s│ Type: GROUP (nested commands)\n", indent);
            print_redirection_info(group, indent);
            printf("%s└─┬─────────────────────────────\n", indent);
            
            if (group->data)
                print_group((t_group *)group->data, depth + 1, group);
        }
        else if (group->data_type == CMD \
            || (group->data_type >= INCMD_ECHO && group->data_type <= STD_CMD))
        {
            t_tokens	*tokens;
            
            tokens = NULL;
            if (group->data)
                tokens = (t_tokens *)group->data;
                
            printf("%s│ Type: COMMAND [%s]\n", indent, token_type_to_str(group->data_type));
            
            if (tokens && tokens->content && tokens->type && tokens->size > 0)
            {
                size_t	i;

                printf("%s│ Tokens (%zu):\n", indent, tokens->size);
                i = 0;
                while (i < tokens->size && i < 100)
                {
                    if (i < tokens->size)
                    {
                        printf("%s│  %zu. '%s' [%s]\n", 
                            indent, i + 1, 
                            tokens->content[i] ? tokens->content[i] : "(null)",
                            token_type_to_str(tokens->type[i]));
                    }
                    i++;
                }
            }
            else
            {
                printf("%s│ [No Tokens]\n", indent);
            }
            
            print_redirection_info(group, indent);
            printf("%s└───────────────────────────────\n", indent);
        }
        else
        {
            printf("%s│ Type: UNKNOWN (%d)\n", indent, group->data_type);
            printf("%s└───────────────────────────────\n", indent);
        }
        
        if (group->next)
        {
            printf("%s▼ Next Group ▼\n", indent);
        }
        
        next = group->next;
        group = next;
    }
}

// Wrapper function for calling from main
void	grouped_tokens_display(t_group *group)
{
    printf("\n========== COMMAND STRUCTURE ==========\n");
    if (!group)
    {
        printf("No commands (NULL)\n");
        return ;
    }
    
    print_group(group, 0, NULL);
    printf("=======================================\n\n");
}

/**
 * START OF VISUALISATION PART FOR TOKENS
 */
void	print_tokens(t_tokens *tokens)
{
    size_t	i;

    if (!tokens)
    {
        printf("Tokens: NULL\n");
        return ;
    }
    
    printf("--- TOKENS ---\n");
    printf("Token count: %zu\n", tokens->size);
    
    i = 0;
    while (i < tokens->size)
    {
        printf("[%zu] Type: %s, Content: \"", i, 
            token_type_to_str(tokens->type[i]));
        if (tokens->content[i])
            printf("%s", tokens->content[i]);
        else
            printf("(NULL)");
        printf("\"\n");
        i++;
    }
    printf("--- END TOKENS ---\n");
}
