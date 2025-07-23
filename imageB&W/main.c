#include <stdio.h>
#include <stdlib.h>
#include <jpeglib.h>

void convert_to_gray_scale(JSAMPLE *image_buffer, int width, int height) {
    // Función para convertir la imagen a blanco y negro puro (blanco o negro)
    // Recorre cada píxel y aplica un umbral al valor en escala de grises
    for (int i = 0; i < width * height; i++) {
        // Obtener los valores RGB del píxel i
        int r = image_buffer[i * 3 + 0];
        int g = image_buffer[i * 3 + 1];
        int b = image_buffer[i * 3 + 2];

        // Calcular el gris 
        int gray = (int)(0.3 * r + 0.59 * g + 0.11 * b);

        //Remplazar el valor de gris en cada pixel
        image_buffer[i * 3 + 0] = gray;
        image_buffer[i * 3 + 1] = gray;
        image_buffer[i * 3 + 2] = gray;
    }
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Uso: %s <imagen_entrada.jpg> <imagen_salida.jpg>\n", argv[0]);
        return 1;
    }
    //Se aceptan los parametros de imagen, el primer parametro como archivo de entrada y el segundo sera el nombre de salida del archivo.
    const char *input_filename = argv[1];
    const char *output_filename = argv[2];

    //Inicializamos las instancias necesarias de la libreria
    struct jpeg_decompress_struct cinfo; //Estructura de descompresion
    struct jpeg_compress_struct cinfo_out; //Estructura de compresion
    struct jpeg_error_mgr jerr; //Manejador de errores de libjpeg

    // Abrir archivo de entrada en modo lectura binaria
    FILE *input_file = fopen(input_filename, "rb");
    if (!input_file) {
        fprintf(stderr, "No se puede abrir %s\n", input_filename);
        return 1;
    }
    // Configurar el manejador de errores para la descompresión
    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_decompress(&cinfo);  // Inicializar descompresor JPEG
    jpeg_stdio_src(&cinfo, input_file); // Establecer fuente desde el archivo
    jpeg_read_header(&cinfo, TRUE); // Leer cabecera JPEG
    jpeg_start_decompress(&cinfo);  // Comenzar la descompresión

    // Obtener dimensiones y canales de la imagen
    int width = cinfo.output_width;
    int height = cinfo.output_height;
    int channels = cinfo.output_components; // 3 Canales del RGB

    // Reservar memoria suficiente para almacenar toda la imagen
    JSAMPLE *image_buffer = (JSAMPLE *)malloc(width * height * channels);
    if (!image_buffer) {
        fprintf(stderr, "Error al asignar memoria.\n");
        return 1;
    }

    JSAMPROW row_pointer[1]; // Puntero para leer línea por línea
        
    // Leer cada línea de la imagen y guardarla en el buffer
    while (cinfo.output_scanline < height) {
        row_pointer[0] = &image_buffer[cinfo.output_scanline * width * channels];
        jpeg_read_scanlines(&cinfo, row_pointer, 1);
    }

    // Finalizar y limpiar la descompresión
    jpeg_finish_decompress(&cinfo);
    jpeg_destroy_decompress(&cinfo);
    fclose(input_file);

    // Convertir la imagen cargada a escala de grises
    convert_to_gray_scale(image_buffer, width, height);

    // Abrir archivo de salida en modo escritura binaria
    FILE *output_file = fopen(output_filename, "wb");
    if (!output_file) {
        fprintf(stderr, "No se puede crear %s\n", output_filename);
        free(image_buffer);
        return 1;
    }

    // Configurar el manejador de errores para la compresión
    cinfo_out.err = jpeg_std_error(&jerr);
    jpeg_create_compress(&cinfo_out);
    jpeg_stdio_dest(&cinfo_out, output_file); // Establecer destino al archivo

    // Establecer parámetros de la imagen para la compresión
    cinfo_out.image_width = width;
    cinfo_out.image_height = height;
    cinfo_out.input_components = channels;
    cinfo_out.in_color_space = JCS_RGB;

    jpeg_set_defaults(&cinfo_out);
    jpeg_start_compress(&cinfo_out, TRUE); // Comenzar compresión

    // Escribir la imagen modificada línea por línea al archivo de salida
    while (cinfo_out.next_scanline < height) {
        row_pointer[0] = &image_buffer[cinfo_out.next_scanline * width * channels];
        jpeg_write_scanlines(&cinfo_out, row_pointer, 1);
    }

    // Finalizar y limpiar la compresión
    jpeg_finish_compress(&cinfo_out);
    jpeg_destroy_compress(&cinfo_out);
    fclose(output_file);

    // Liberar la memoria reservada para la imagen
    free(image_buffer);

    // Informar que el proceso terminó exitosamente
    printf("Imagen convertida exitosamente a escala de grises: %s\n", output_filename);
    return 0;
}
