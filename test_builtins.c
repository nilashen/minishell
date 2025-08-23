/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nashena <nashena@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 11:57:01 by nashena           #+#    #+#             */
/*   Updated: 2025/08/22 12:13:19 by nashena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void test_pwd(void)
{
    print_test_header("PWD");
    
    ft_printf("Current directory: ");
    int result = mysh_pwd();
    print_test_result("pwd", result);
}

void test_env(char **envp)
{
    print_test_header("ENV");
    
    int result = mysh_env(envp);
    print_test_result("env", result);
}
void test_echo(void)
{
    char **test_args;
    int result;
    
    print_test_header("ECHO");
    
    ft_printf("\nTest 1: echo hello\n");
    test_args = create_test_args("echo", "hello", NULL);
    result = mysh_echo(test_args);
    free(test_args);
    print_test_result("echo hello", result);
    
    ft_printf("\nTest 2: echo -n hello (no newline)\n");
    test_args = create_test_args("echo", "-n", "hello");
    result = mysh_echo(test_args);
    free(test_args);
    ft_printf(" <-- should be no newline after hello\n");
    print_test_result("echo -n hello", result);
    
    ft_printf("\nTest 3: echo hello world\n");
    char *multi_args[] = {"hello", "world", "test"};
    test_args = create_test_args_multiple("echo", multi_args, 3);
    result = mysh_echo(test_args);
    free(test_args);
    print_test_result("echo multiple args", result);
    
    ft_printf("\nTest 4: echo (no args)\n");
    test_args = create_test_args("echo", NULL, NULL);
    result = mysh_echo(test_args);
    free(test_args);
    print_test_result("echo empty", result);
}

void test_cd(char **envp)
{
    char **test_envp;
    char **test_args;
    int result;
    
    print_test_header("CD");
    test_envp = copy_environment(envp);
    
    ft_printf("\nTest 1: cd (go to home)\n");
    test_args = create_test_args("cd", NULL, NULL);
    result = mysh_cd(test_args, &test_envp);
    free(test_args);
    print_test_result("cd home", result);
    mysh_pwd();
    
    ft_printf("\nTest 2: cd /tmp\n");
    test_args = create_test_args("cd", "/tmp", NULL);
    result = mysh_cd(test_args, &test_envp);
    free(test_args);
    print_test_result("cd /tmp", result);
    mysh_pwd();
    
    ft_printf("\nTest 3: cd /nonexistent\n");
    test_args = create_test_args("cd", "/nonexistent", NULL);
    result = mysh_cd(test_args, &test_envp);
    free(test_args);
    print_test_result("cd invalid", result);
    
    ft_printf("\nTest 4: cd arg1 arg2 (too many args)\n");
    test_args = create_test_args("cd", "arg1", "arg2");
    result = mysh_cd(test_args, &test_envp);
    free(test_args);
    print_test_result("cd too many args", result);
    
    free_environment(test_envp);
}

void test_export(char **envp)
{
    char **test_envp;
    char **test_args;
    int result;
    
    print_test_header("EXPORT");
    test_envp = copy_environment(envp);
    
    ft_printf("\nTest 1: export (display all exported variables)\n");
    test_args = create_test_args("export", NULL, NULL);
    result = mysh_export(test_args, &test_envp);
    free_test_args(test_args);
    print_test_result("export display", result);
    
    ft_printf("\nTest 2: export TEST_VAR=hello\n");
    test_args = create_test_args("export", "TEST_VAR=hello", NULL);
    result = mysh_export(test_args, &test_envp);
	free_test_args(test_args);
    print_test_result("export VAR=value", result);
    
    ft_printf("\nTest 3: export PATH (existing variable)\n");
    test_args = create_test_args("export", "PATH", NULL);
    result = mysh_export(test_args, &test_envp);
    free_test_args(test_args);
    print_test_result("export existing var", result);
    
    ft_printf("\nTest 4: export NEW_VAR (create empty)\n");
    test_args = create_test_args("export", "NEW_VAR", NULL);
    result = mysh_export(test_args, &test_envp);
    free_test_args(test_args);
    print_test_result("export new var empty", result);
    
    ft_printf("\nTest 5: export EMPTY_VAR=\n");
    test_args = create_test_args("export", "EMPTY_VAR=", NULL);
    result = mysh_export(test_args, &test_envp);
    free_test_args(test_args);
    print_test_result("export empty value", result);
    
    ft_printf("\nTest 6: export VAR1=value1 VAR2=value2\n");
    char *multi_exports[] = {"VAR1=value1", "VAR2=value2", "VAR3=value3"};
    test_args = create_test_args_multiple("export", multi_exports, 3);
    result = mysh_export(test_args, &test_envp);
    free_test_args(test_args);
    print_test_result("export multiple", result);
    
    ft_printf("\nTest 7: export 123INVALID=value (should fail)\n");
    test_args = create_test_args("export", "123INVALID=value", NULL);
    result = mysh_export(test_args, &test_envp);
    free_test_args(test_args);
    print_test_result("export invalid identifier", result);
    
    ft_printf("\nTest 8: export SPECIAL=\"value with spaces\"\n");
    test_args = create_test_args("export", "SPECIAL=value with spaces", NULL);
    result = mysh_export(test_args, &test_envp);
    free_test_args(test_args);
    print_test_result("export with spaces", result);
    
    ft_printf("\nTest 9: export =value (should fail)\n");
    test_args = create_test_args("export", "=value", NULL);
    result = mysh_export(test_args, &test_envp);
    free_test_args(test_args);
    print_test_result("export no name", result);
    
    free_environment(test_envp);
}

void test_unset(char **envp)
{
    char **test_envp;
    char **test_args;
    int result;
    
    print_test_header("UNSET");
    test_envp = copy_environment(envp);
    
    test_args = create_test_args("export", "TEST_UNSET=value", NULL);
    mysh_export(test_args, &test_envp);
    free(test_args);
    
    ft_printf("\nTest 1: unset TEST_UNSET\n");
    test_args = create_test_args("unset", "TEST_UNSET", NULL);
    result = mysh_unset(test_args, &test_envp);
    free(test_args);
    print_test_result("unset existing", result);
    
    ft_printf("\nTest 2: unset NONEXISTENT\n");
    test_args = create_test_args("unset", "NONEXISTENT", NULL);
    result = mysh_unset(test_args, &test_envp);
    free(test_args);
    print_test_result("unset nonexistent", result);
    
    ft_printf("\nTest 3: unset 123INVALID\n");
    test_args = create_test_args("unset", "123INVALID", NULL);
    result = mysh_unset(test_args, &test_envp);
    free(test_args);
    print_test_result("unset invalid", result);
    
    free_environment(test_envp);
}