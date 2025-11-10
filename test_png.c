#include "MLX42/include/MLX42/MLX42.h"
#include <stdio.h>

int	main(void)
{
	mlx_t *mlx = mlx_init(800, 600, "Test", true);
	if (!mlx)
	{
		printf("MLX init failed\n");
		return (1);
	}

	printf("MLX initialized successfully\n");

	mlx_texture_t *texture = mlx_load_png("./textures/test_red.png");
	if (!texture)
	{
		printf("❌ Failed to load PNG\n");
		mlx_terminate(mlx);
		return (1);
	}

	printf("✅ PNG loaded successfully: %dx%d\n", texture->width,
		texture->height);

	mlx_delete_texture(texture);
	mlx_terminate(mlx);
	return (0);
}