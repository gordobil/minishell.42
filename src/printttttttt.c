
#include "../includes/minishell.h"

void	printttttttt(t_mini	*mini)
{
	t_pipes	*command = mini->pipes;

	ft_printf("\n\nMATRIX\n----------------\n%m----------------\n\n\n", mini->arg_matrix);
	while (command != NULL)
	{
		ft_printf("NODE [%d]\n\n%m", command->position, command->command);
		ft_printf("\nFiles:\nin:%s out:%s app:%s del:%s\n\n.............\n\n", command->infile->file, command->outfile->file, command->append->file, command->delimiter->file);
		command = command->next;
	}
	ft_printf("Command count: %d\n\n", mini->comm_c);
	ft_printf("File count: %d\n\n", mini->file_c);
	if (mini->files)
		ft_printf("%m\n", mini->files);
	ft_printf("Delimiter count: %d\n\n", mini->del_c);
	if (mini->delimiters)
		ft_printf("%m\n", mini->delimiters);
	
}
