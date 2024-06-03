import subprocess

def run_main_and_save_image():
    try:
        # Execute o executável main e redirecione a saída para um arquivo de imagem
        subprocess.run(["./main"], check=True, stdout=open("output_image.png", "wb"))
        print("Imagem gerada com sucesso!")
    except subprocess.CalledProcessError as e:
        # Se ocorrer um erro ao chamar o processo, imprima uma mensagem de erro
        print(f"Erro ao executar o programa: {e}")
    except FileNotFoundError:
        # Se o arquivo executável não for encontrado, imprima uma mensagem de erro
        print("Arquivo executável não encontrado.")

if __name__ == "__main__":
    run_main_and_save_image()
